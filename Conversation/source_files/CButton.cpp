/*
 * CButton.cpp
 *
 *  Created on: 05.08.2010
 *      Author: Martu
 */

#include "Conversation/CButton.hpp"

// Initializes a button
void CButton::Init (std::string FileName,
					sf::Vector2i FrameSize,
					int State)
{
	std::string tmp;
	tmp.append ("Buttons/");
	tmp.append (FileName);

	m_StdState     = State;
	m_ButtonState  = m_StdState;

	m_ButtonSprite.Init(tmp, FrameSize.x, FrameSize.y);
}

// returns true if the Mouse is over the button, the coordinates of the mouse have
// to converted to local ones OUTSIDE this function
bool CButton::IsMouseOver (int MouseX, int MouseY)
{
	sf::IntRect  BB = GetBoundingBox ();

	if (MouseX >= BB.Left && MouseX <= BB.Right &&
		MouseY >= BB.Top  && MouseY <= BB.Bottom)
		return true;
	else
		return false;
}

// creates a normal bounding box for this button, no rotated buttons are supported
sf::IntRect CButton::GetBoundingBox ()
{
	sf::IntRect BB;

	BB.Left   = static_cast<int> (m_ButtonSprite.GetPosition ().x);
	BB.Right  = BB.Left + (m_ButtonSprite.GetSubRect ().Right - m_ButtonSprite.GetSubRect ().Left);
	BB.Top    = static_cast<int> (m_ButtonSprite.GetPosition ().y);
	BB.Bottom = BB.Top + (m_ButtonSprite.GetSubRect ().Bottom - m_ButtonSprite.GetSubRect ().Top);

	return BB;
}

