/*
 * CFadeEffect.cpp
 *
 *  Created on: 04.09.2010
 *      Author: Martu
 */

#include "Conversation/CFadeEffect.hpp"
#include "Conversation/CFXSprite.hpp"

// initializes the FadeEffect
void CFadeEffect::Start  (CFXSprite &Sprite, float fTargetValue, float fDuration)
{
	m_fStartingAlpha = Sprite.GetColor ().a;
	m_fCurrentAlpha  = m_fStartingAlpha;
	m_fDuration      = fDuration;

	m_Timer.Reset ();

	// test if the Target Value is valid
	if (fTargetValue >= 0 && fTargetValue <= 255)
		m_fTargetAlpha = fTargetValue;
	else if (fTargetValue < 0)
		m_fTargetAlpha = 0;
	else if (fTargetValue > 255)
		m_fTargetAlpha = 255;

	m_fDifference = m_fTargetAlpha - m_fStartingAlpha;

	m_bIsActive = true;
	m_bDelay    = false;
}

// Initializes the FadeEffect with a starting value
void CFadeEffect::Start  (CFXSprite &Sprite, float fStartingValue, float fTargetValue, float fDuration)
{
	// test if the starting value is valid
	if (fStartingValue < 0)
		fStartingValue = 0;
	else if (fStartingValue > 255)
		fStartingValue = 255;

	// no set the starting value
	Sprite.SetColor (sf::Color (Sprite.GetColor ().r,
								Sprite.GetColor ().g,
								Sprite.GetColor ().b,
								static_cast<sf::Uint8> (fStartingValue)));

	Start (Sprite, fTargetValue, fDuration);
}

// stops the Fading
void CFadeEffect::Stop   (CFXSprite &Sprite, bool bCancel)
{
	m_bIsActive = false;

	// if cancel == true, reset the original alpha value
	if (bCancel)
	{
		sf::Color Original;
		Original = Sprite.GetColor ();
		Original.a = static_cast<sf::Uint8> (m_fStartingAlpha);
		Sprite.SetColor (Original);
	}

	// reset the variables
	m_fStartingAlpha = 0;
	m_fTargetAlpha   = 0;
	m_fCurrentAlpha  = 0;
	m_fDifference    = 0;
	m_fDelay         = 0;
}

// Updates the Alpha value of the Sprite
void CFadeEffect::Update (CFXSprite &Sprite)
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
			// set the alpha to the target alpha
			Sprite.SetColor (sf::Color (Sprite.GetColor ().r,
										Sprite.GetColor ().g,
										Sprite.GetColor ().b,
										static_cast<sf::Uint8> (m_fTargetAlpha)));

			// and stop the effect (not cancel it)
			Stop (Sprite, false);
		}
		else
		{
			// calculate the current alpha value
			m_fCurrentAlpha = m_fStartingAlpha + (m_fDifference * (m_Timer.GetElapsedTime () / m_fDuration));
			Sprite.SetColor (sf::Color (Sprite.GetColor ().r,
										Sprite.GetColor ().g,
										Sprite.GetColor ().b,
										static_cast<sf::Uint8> (m_fCurrentAlpha)));
		}
	}
}
