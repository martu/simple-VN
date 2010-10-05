/*
 * CShakeEffect.cpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#include "Conversation/CShakeEffect.hpp"
#include "Conversation/CFXSprite.hpp"

// initializes the FadeEffect (when the duration is -1, the effect runs until stop is called
void CShakeEffect::Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fOptional, float fDuration)
{
	m_MaxShake         = TargetValue;
	m_StartingPosition = Sprite.GetPosition ();
	m_CurrentPosition  = m_StartingPosition;
	m_OldPosition      = m_StartingPosition;
	m_fShakeSpeed      = fOptional;
	m_fDuration        = fDuration;
	m_fCurrentDuration = 0;
	m_fShakeDuration   = 0;

	m_Timer.Reset ();

	CalculateNewPosition ();

	m_bIsActive = true;
	m_bDelay    = false;
}

// stops the Shaking
void CShakeEffect::Stop   (CFXSprite &Sprite, bool bCancel)
{
	m_bIsActive = false;

	// if cancel == true, reset the original alpha value
	if (bCancel)
		Sprite.SetPosition (m_StartingPosition);

	// reset the variables
	m_MaxShake.x = 0;
	m_MaxShake.y = 0;

	m_StartingPosition.x = 0;
	m_StartingPosition.y = 0;

	m_OldPosition.x = 0;
	m_OldPosition.y = 0;

	m_TargetPosition.x = 0;
	m_TargetPosition.y = 0;

	m_CurrentPosition.x = 0;
	m_CurrentPosition.y = 0;

	m_Difference.x = 0;
	m_Difference.y = 0;

	m_fShakeSpeed = 0;
	m_fCurrentDuration = 0;
	m_fShakeDuration   = 0;

	m_fDelay = 0;
}

// Updates the Shaking of the Sprite
void CShakeEffect::Update (CFXSprite &Sprite)
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
		// update the timer
		m_fCurrentDuration += m_Timer.GetElapsedTime ();
		m_fShakeDuration   += m_Timer.GetElapsedTime ();

		// and reset the clock
		m_Timer.Reset ();

		// test if the duration is reached
		if (m_fShakeDuration >= m_fShakeSpeed)
		{
			// set the current position to the target position
			Sprite.SetPosition (m_TargetPosition);
			m_CurrentPosition = m_TargetPosition;

			// and calculate a new one
			CalculateNewPosition ();

			// and reset the timer
			m_fShakeDuration = 0;
		}
		else
		{
			// calculate the current position
			m_CurrentPosition = m_OldPosition + (m_Difference * (m_fShakeDuration / m_fShakeSpeed));
			Sprite.SetPosition (m_CurrentPosition);
		}

		// test if we should stop this effect
		if (m_fCurrentDuration >= m_fDuration && m_fDuration != -1)
			Stop (Sprite);
	}
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// calculates a new random position for the sprite
void CShakeEffect::CalculateNewPosition ()
{
	m_OldPosition = m_CurrentPosition;

	m_TargetPosition.x = m_StartingPosition.x + sf::Randomizer::Random (-m_MaxShake.x, m_MaxShake.x);
	m_TargetPosition.y = m_StartingPosition.y + sf::Randomizer::Random (-m_MaxShake.y, m_MaxShake.y);

	m_Difference = m_TargetPosition - m_CurrentPosition;
}
