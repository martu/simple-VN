/*
 * CTextarea.hpp
 *
 *  Created on: 25.08.2010
 *      Author: Martu
 */

#ifndef CTEXTAREA_HPP_
#define CTEXTAREA_HPP_

#include "CFXSprite.hpp"
#include "CImageManager.hpp"
#include "CFontManager.hpp"

// describes a class which is used for creating a text area for the game
class CTextArea
{
private:
	sf::Vector2f m_Position; // Position of the Area
	sf::Vector2f m_Size;     // Size of the Area (Ignored when a sprite is the background)

	CFXSprite    m_BackgroundSprite;

	bool         m_bCursor;       // if the cursor should displayed or not
	bool         m_bIsActive;     // If the complete text is displayed or not
	float        m_fCursorBlinkSpeed;  // Speed for the Blinking of the Cursor
	float        m_fElapsedTimeCursor; // Elapsed time for the Cursor Blinking
	float        m_fTextSpeed;    // speed for the single characters of the Text to appear
	float        m_fElapsedTime;  // Elapsed time for the Text
	float        m_fCurAlpha;     // Current alpha value of the text, used for scenechanges while fading
	int          m_CurPos;        // current number of character to display
	string       m_sCompleteText; // complete Text
	string       m_sPartText;     // Part of the Text to display
	sf::String   m_sDisplayText;  // characters which should be displayed
	sf::String   m_sSpeakerName;  // Name of the Speaker
	sf::Color    m_SpeakerColor;  // Color for the Speaker
	sf::Color    m_MessageColor;  // Color for normal messages
	sf::Color    m_ReadMessageColor; // Color for read messages

public:
	void Init (sf::Vector2f Position, sf::Vector2f Size, string Font, int FontSize, float fSpeed, float fBlinkSpeed);

	void SetBackgroundSprite (string BGSprite);
	void SetBackgroundColor  (sf::Color BGColor);
	void SetTextColor        (sf::Color Text, sf::Color ReadMessage);
	void SetTextColor        (sf::Color Text, sf::Color ReadMessage, sf::Color Speaker);
	void SetSpeakerPosition  (sf::Vector2f Position);
	void SetTextPosition     (sf::Vector2f Position);
	void SetText             (string sSpeaker, string sText, bool bIsRead = false);
	void SetFade             (float from, float to, float duration);

	bool IsActive () {return m_bIsActive;};

	void DisplayAll ();
	void Update (float fElapsed);
	void Render (sf::RenderWindow *pWindow);
};


#endif /* CTEXTAREA_HPP_ */
