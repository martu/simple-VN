/*
 * CFXEffect.hpp
 *
 *  Created on: 04.09.2010
 *      Author: Martu
 */

#ifndef CFXEFFECT_HPP_
#define CFXEFFECT_HPP_

#include <SFML/Graphics.hpp>

class CFXSprite;

// defines a base class for the different sprite effects
class CFXEffect
{
protected:
	bool  m_bIsActive; // if the effect is currently active or not
	bool  m_bDelay;    // if the Delay is over or not
	float m_fDuration; // how long the effect should be active
	float m_fDelay;    // if the effect should start after some delay

	sf::Clock m_Timer; // because I don't have the framework here I need another Timer

public:
	CFXEffect () {m_bIsActive = false;m_bDelay = false; m_fDuration = 0; m_fDelay = 0;};
	virtual ~CFXEffect () {};

	virtual void Start  (CFXSprite &Sprite, float fTargetValue, float fDuration) {};
	virtual void Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fDuration) {};
	virtual void Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fOptional, float fDuration) {};
	virtual void Start  (CFXSprite &Sprite, float fStartingValue, float fTargetValue, float fDuration) {};
	virtual void Start  (CFXSprite &Sprite, sf::Vector2f StartingValue, sf::Vector2f TargetValue, float fDuration) {};

	virtual void SetSize (sf::Vector2f Size) {};

	virtual void Stop   (CFXSprite &Sprite, bool bCancel = true) = 0;
	virtual void Update (CFXSprite &Sprite) = 0;

	void  SetToTarget () {m_fDuration = 0; m_fDelay = 0;};
	void  SetDelay    (float fDelay) {m_fDelay = fDelay; m_bDelay = true; m_bIsActive = false;};
	bool  IsActive    () {return m_bIsActive;};
	float GetDuration () {return m_fDuration;};
};

#endif /* CFXEFFECT_HPP_ */
