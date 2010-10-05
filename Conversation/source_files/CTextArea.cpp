/*
 * CTextarea.cpp
 *
 *  Created on: 25.08.2010
 *      Author: Martu
 */

#include "Conversation/CTextarea.hpp"

// Basic initialization, before the object can be used we have to set additionally variables
void CTextArea::Init (sf::Vector2f Position, sf::Vector2f Size, string Font, int FontSize, float fSpeed, float fBlinkSpeed)
{
	m_bCursor    = false;
	m_Position   = Position;
	m_Size       = Size;
	m_fTextSpeed = fSpeed;
	m_fCursorBlinkSpeed = fBlinkSpeed;
	m_fCurAlpha   = 255;

	m_sDisplayText.SetFont (g_pFontManager->getFont(Font, FontSize) );
	m_sDisplayText.SetSize (FontSize);
	m_sSpeakerName.SetFont  (g_pFontManager->getFont(Font, FontSize) );
	m_sSpeakerName.SetSize (FontSize);
}

// Sets the Background Sprite
void CTextArea::SetBackgroundSprite (string BGSprite)
{
	m_BackgroundSprite.SetPosition (m_Position);
	m_BackgroundSprite.SetImage    (g_pImageManager->getImage(BGSprite) );
}

// Sets a color for the Background
void CTextArea::SetBackgroundColor (sf::Color BGColor)
{
	m_BackgroundSprite.SetPosition (m_Position);
	m_BackgroundSprite.SetScale    (m_Size);
	m_BackgroundSprite.SetColor    (BGColor);
}

// Sets the different Colors
void CTextArea::SetTextColor (sf::Color Text, sf::Color ReadMessage)
{
	m_MessageColor     = Text;
	m_ReadMessageColor = ReadMessage;
	m_SpeakerColor     = Text; // when the speaker shouldn't have any special color, use the normal one
}

// Sets the different Colors ( this time with another extra color for the speaker
void CTextArea::SetTextColor (sf::Color Text, sf::Color ReadMessage, sf::Color Speaker)
{
	SetTextColor (Text, ReadMessage);
	m_SpeakerColor = Speaker;
}

// Sets the Position of the Speaker Name, relative to the upper left corner of the area
void CTextArea::SetSpeakerPosition (sf::Vector2f Position)
{
	sf::Vector2f tmp;

	tmp.x = m_Position.x + Position.x;
	tmp.y = m_Position.y + Position.y;

	m_sSpeakerName.SetPosition (tmp);
}

// Sets the Position of the Text, relative to the upper left corner of the Area
void CTextArea::SetTextPosition (sf::Vector2f Position)
{
	sf::Vector2f tmp;

	tmp.x = m_Position.x + Position.x;
	tmp.y = m_Position.y + Position.y;

	m_sDisplayText.SetPosition (tmp);
}

// Sets the Text to Display
void CTextArea::SetText (string sSpeaker, string sText, bool bIsRead)
{
	m_sSpeakerName.SetText  (sSpeaker);

	m_sCompleteText.clear ();
	m_sCompleteText.append (sText);

	m_sPartText.clear ();

	// Set the Colors
	if (bIsRead == false)
	{
		// set the normal TextColors
		m_sDisplayText.SetColor (sf::Color (m_MessageColor.r,
											m_MessageColor.g,
											m_MessageColor.b,
											static_cast<sf::Uint8> (m_fCurAlpha)));
		m_sSpeakerName.SetColor (sf::Color (m_SpeakerColor.r,
											m_SpeakerColor.g,
											m_SpeakerColor.b,
											static_cast<sf::Uint8> (m_fCurAlpha)));
	}
	else
	{
		// Set the color for already read messages
		m_sDisplayText.SetColor (sf::Color (m_ReadMessageColor.r,
											m_ReadMessageColor.g,
											m_ReadMessageColor.b,
											static_cast<sf::Uint8> (m_fCurAlpha)));
		m_sSpeakerName.SetColor (sf::Color (m_ReadMessageColor.r,
											 m_ReadMessageColor.g,
											 m_ReadMessageColor.b,
											 static_cast<sf::Uint8> (m_fCurAlpha)));
	}

	// Reset the Position and the Time
	m_CurPos = -1; // because the first position is 0
	m_fElapsedTime = 0.0f;
	m_fElapsedTimeCursor = 0.0f;
	m_bIsActive = true;
}

void CTextArea::SetFade (float from, float to, float duration)
{
	// now add the actual effect
	m_BackgroundSprite.AddEffect     (new CFadeEffect);
	m_BackgroundSprite.GetLastEffect ()->Start (m_BackgroundSprite, from, to, duration);

	// As long as I can't add a fade effect to text, just set it directly to the final value
	m_sSpeakerName.SetColor     (sf::Color (m_sSpeakerName.GetColor ().r,
											m_sSpeakerName.GetColor ().g,
											m_sSpeakerName.GetColor ().b,
											static_cast<sf::Uint8> (to)));
	m_sDisplayText.SetColor     (sf::Color (m_sDisplayText.GetColor ().r,
											m_sDisplayText.GetColor ().g,
											m_sDisplayText.GetColor ().b,
											static_cast<sf::Uint8> (to)));

	m_fCurAlpha = to;
}

// Instantly displays the complete text
void CTextArea::DisplayAll ()
{
	m_sPartText.assign (m_sCompleteText);
	m_CurPos = static_cast<int> (m_sCompleteText.size () );
	m_bIsActive = false;
}

// Updates the Textarea (used for displaying the Text character for character)
void CTextArea::Update (float fElapsed)
{
	m_fElapsedTime += fElapsed;
	m_fElapsedTimeCursor += fElapsed;

	// check if the cursor should be displayed or not
	if (m_fElapsedTimeCursor >= m_fCursorBlinkSpeed)
	{
		m_bCursor = !m_bCursor;
		m_fElapsedTimeCursor = 0.0f;
	}

	int MaxPos = static_cast<int> (m_sCompleteText.size () );

	// Check if the next character should be displayed
	if (m_fElapsedTime >= m_fTextSpeed)
	{
		m_CurPos++;

		// Check if the new Position is valid
		if (m_CurPos < MaxPos )
		{
			// append the next character
			m_sPartText.push_back (m_sCompleteText.at (m_CurPos) );

			// Set the new Text
			m_sDisplayText.SetText (m_sPartText);
			m_bIsActive = true;
		}
		else if (m_CurPos >= MaxPos && m_bCursor) // when the cursor should be displayed
		{
			m_sDisplayText.SetText (m_sPartText + " _");
			m_bIsActive = false;
		}
		else if (m_CurPos >= MaxPos && !m_bCursor) // when the cursor shouldn't be displayed
		{
			m_sDisplayText.SetText (m_sPartText);
			m_bIsActive = false;
		}

		// Reset the Time
		m_fElapsedTime = 0.0f;
	}

	// also update the BackgroundSprite, in case there are any effects applied
	m_BackgroundSprite.Update ();
}

// Render the whole thing
void CTextArea::Render (sf::RenderWindow *pWindow)
{
	// First the Background
	pWindow->Draw (m_BackgroundSprite);

	// Now the Name of the Speaker
	pWindow->Draw (m_sSpeakerName);

	// And now the actual Text
	pWindow->Draw (m_sDisplayText);
}
