/*
 * CChoice.cpp
 *
 *  Created on: 30.08.2010
 *      Author: Martu
 */

#include "Conversation/CChoice.hpp"

// Renders the Chocie button
void CChoice::Render (sf::RenderWindow *pWindow)
{
	// TODO only recompute when necessary
	ComputeNamePos ();

	m_ButtonSprite.Calculate (m_ButtonState-1);

	// Now Render the Name
	pWindow->Draw (m_ButtonSprite);
	pWindow->Draw (m_sName);
}

// Sets the Font for the Name of the Button
void CChoice::SetFont (string sFont)
{
	m_sName.SetFont (g_pFontManager->getFont (sFont) );
}

// Sets the Name of the Button, and the Flag
void CChoice::SetChoice (string sName, string sFlag)
{
	m_sFlag = sFlag;

	m_sName.SetText (sName);

	// compute the Position
	ComputeNamePos ();
}

// When the Mouse is Over set the State to MouseOver
void CChoice::SetMouseOver (bool MouseOver)
{
	if (MouseOver)
		SetState (CButton::MOUSEOVER);
	else
		SetState (CButton::ACTIVATED);
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// computes the Position of the Button-Name, so that it is always centered on the Sprite
void CChoice::ComputeNamePos ()
{
	sf::Vector2f tmp;

	tmp.x = m_ButtonSprite.GetPosition ().x + (m_ButtonSprite.GetFrameSize ().x / 2 - m_sName.GetRect ().GetWidth  () / 2);
	tmp.y = m_ButtonSprite.GetPosition ().y + (m_ButtonSprite.GetFrameSize ().y / 2 - m_sName.GetRect ().GetHeight () / 2);

	m_sName.SetPosition (tmp);
}
