/*
 * CButton.hpp
 *
 *  Created on: 05.08.2010
 *      Author: Martu
 */

#ifndef CBUTTON_HPP_
#define CBUTTON_HPP_

#include "CAniSprite.hpp"

using namespace std;

// class which represents a button, used as a base class
class CButton
{
protected:
	int m_StdState;     // normal state of the button
	int m_ButtonState;  // current state of the button

public:
	// PUBLIC because it makes the rendering easier and makes the handling
	// of the class easier (no additional functions for setting the position, rotation, ...)
	CAniSprite m_ButtonSprite;  // Sprite for the button

	virtual ~CButton () {};

	// Initializes a SPRITEONLY button
	void Init (std::string FileName,
			   sf::Vector2i FrameSize,
			   int State = CButton::ACTIVATED);

	bool IsMouseOver (int MouseX, int MouseY);

	void SetState (int NewState) {m_ButtonState = NewState;};

	int GetState () {return m_ButtonState;};
	void ResetState () {m_ButtonState = m_StdState;};

	sf::IntRect GetBoundingBox ();

	void Update () {m_ButtonSprite.Calculate (m_ButtonState);};

	// what state the button is in (invisible, activated...)
	// also acts as an enum defining the numbers of the frames
	enum BUTTONSTATE
	{
		INVISIBLE = -1,   // the button is not being rendered
		DEACTIVATED,      // the button is not clickable
		ACTIVATED,        // the button is rendered normally and is clickable
		MOUSEOVER,        // the mouse is over the button, so highlight it
	};
};

#endif /* CBUTTON_HPP_ */
