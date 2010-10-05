/*
 * CScrollEffect.cpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#include "Conversation/CScrollEffect.hpp"
#include "Conversation/CFXSprite.hpp"

// initializes the ScrollEffect (SetSize MUST be called otherwise undefined behavior )
void CScrollEffect::Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fDuration)
{
	m_StartingPosition.x = Sprite.GetSubRect ().Left;
	m_StartingPosition.y = Sprite.GetSubRect ().Top;
	m_StartingRect       = Sprite.GetSubRect ();
	m_TargetPosition     = TargetValue;
	m_CurrentPosition    = m_StartingPosition;
	m_SpriteSize.x = Sprite.GetImage ()->GetWidth   ();
	m_SpriteSize.y = Sprite.GetImage ()->GetHeight  ();
	m_Size.x       = Sprite.GetSubRect ().GetWidth  ();
	m_Size.y       = Sprite.GetSubRect ().GetHeight ();
	m_fDuration    = fDuration;

	m_Timer.Reset ();

	m_bIsActive = true;
	m_bDelay    = false;
	m_bCalculated = false;
}

// Initializes the ScrollEffect with a starting value
void CScrollEffect::Start  (CFXSprite &Sprite, sf::Vector2f StartingValue, sf::Vector2f TargetValue, float fDuration)
{
	Sprite.SetSubRect (sf::IntRect (StartingValue.x,
									StartingValue.y,
									StartingValue.x + Sprite.GetSubRect ().GetWidth  (),
									StartingValue.y + Sprite.GetSubRect ().GetHeight () ));

	Start (Sprite, TargetValue, fDuration);
}

// Sets a new size for the SubRect
void CScrollEffect::SetSize (sf::Vector2f Size)
{
	m_Size = Size;

	m_bCalculated = false;
}

// stops the Scrolling
void CScrollEffect::Stop   (CFXSprite &Sprite, bool bCancel)
{
	m_bIsActive = false;

	// if cancel == true, reset the original position value
	if (bCancel)
		Sprite.SetSubRect (m_StartingRect);

	// reset the variables
	m_StartingPosition.x = 0;
	m_StartingPosition.y = 0;

	m_TargetPosition.x   = 0;
	m_TargetPosition.y   = 0;

	m_CurrentPosition.x  = 0;
	m_CurrentPosition.y  = 0;

	m_Difference.x = 0;
	m_Difference.y = 0;

	m_Size.x = 0;
	m_Size.y = 0;

	m_fDelay = 0;
}

// Updates the position of the subrect
void CScrollEffect::Update (CFXSprite &Sprite)
{
	// test if the delay is over
	if (m_bDelay)
	{
		if (m_Timer.GetElapsedTime () >= m_fDelay)
		{
			m_bIsActive = true;
			m_bDelay    = false;
			m_Timer.Reset ();
		}
	}

	// if the effect is active or not
	if (m_bIsActive)
	{
		bool bStop = false;

		if (m_bCalculated == false)
			CalculateTarget ();

		// test if the duration is reached
		if (m_Timer.GetElapsedTime () >= m_fDuration)
		{
			// set the position to the target position
			m_CurrentPosition = m_TargetPosition;

			// and stop the effect (not cancel it)
			bStop = true;
		}
		else
		{
			// calculate the current position
			m_CurrentPosition = m_StartingPosition + (m_Difference * (m_Timer.GetElapsedTime () / m_fDuration));
		}

		// now calculate the position of the subrect and set it
		Sprite.SetSubRect (sf::IntRect (m_CurrentPosition.x,
										m_CurrentPosition.y,
										m_CurrentPosition.x + m_Size.x,
										m_CurrentPosition.y + m_Size.y ));

		if (bStop)
			Stop (Sprite, false);
	}
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// tests if the Target position is valid or not
void CScrollEffect::CalculateTarget ()
{
	if (m_TargetPosition.x + m_Size.x > m_SpriteSize.x)
		m_TargetPosition.x = m_SpriteSize.x - m_Size.x;

	if (m_TargetPosition.x < 0)
		m_TargetPosition.x = 0;

	if (m_TargetPosition.y + m_Size.y > m_SpriteSize.y)
		m_TargetPosition.y = m_SpriteSize.y - m_Size.y;

	if (m_TargetPosition.y < 0)
		m_TargetPosition.y = 0;

	// and calculate the difference
	m_Difference = m_TargetPosition - m_StartingPosition;

	m_bCalculated = true;
}
