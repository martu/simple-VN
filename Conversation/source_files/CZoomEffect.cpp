/*
 * CZoomEffect.cpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#include "Conversation/CZoomEffect.hpp"
#include "Conversation/CFXSprite.hpp"

// initializes the ZoomEffect
void CZoomEffect::Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fDuration)
{
	m_StartingScale = Sprite.GetScale ();
	m_CurrentScale  = m_StartingScale;
	m_TargetScale   = TargetValue;
	m_fDuration     = fDuration;

	m_Timer.Reset ();

	m_Difference = m_TargetScale - m_StartingScale;

	m_bIsActive = true;
	m_bDelay    = false;
}

// Initializes the ZoomEffect with a starting value
void CZoomEffect::Start  (CFXSprite &Sprite, sf::Vector2f StartingValue, sf::Vector2f TargetValue, float fDuration)
{
	Sprite.SetScale (StartingValue);

	Start (Sprite, TargetValue, fDuration);
}

// stops the Zooming
void CZoomEffect::Stop   (CFXSprite &Sprite, bool bCancel)
{
	m_bIsActive = false;

	// if cancel == true, reset the original alpha value
	if (bCancel)
		Sprite.SetScale (m_StartingScale);

	// reset the variables
	m_StartingScale.x = 0;
	m_StartingScale.y = 0;

	m_TargetScale.x   = 0;
	m_TargetScale.y   = 0;

	m_CurrentScale.x  = 0;
	m_CurrentScale.y  = 0;

	m_Difference.x    = 0;
	m_Difference.y    = 0;

	m_fDelay          = 0;
}

// Updates the scale of the sprite
void CZoomEffect::Update (CFXSprite &Sprite)
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
		// test if the duration is reached
		if (m_Timer.GetElapsedTime () >= m_fDuration)
		{
			// set the scale to the target scale
			Sprite.SetScale (m_TargetScale);

			// and stop the effect (not cancel it)
			Stop (Sprite, false);
		}
		else
		{
			// calculate the current scale
			m_CurrentScale = m_StartingScale + (m_Difference * (m_Timer.GetElapsedTime () / m_fDuration));
			Sprite.SetScale (m_CurrentScale);
		}
	}
}
