/*
 * CShakeEffect.hpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#ifndef CSHAKEEFFECT_HPP_
#define CSHAKEEFFECT_HPP_

#include "CFXEffect.hpp"

class CFXSprite;

// defines a simple fade effect for a sprite
class CShakeEffect : public CFXEffect
{
private:
	sf::Vector2f m_MaxShake;
	sf::Vector2f m_StartingPosition;
	sf::Vector2f m_OldPosition;
	sf::Vector2f m_TargetPosition;
	sf::Vector2f m_CurrentPosition;
	sf::Vector2f m_Difference;

	float m_fShakeSpeed;
	float m_fCurrentDuration;
	float m_fShakeDuration;

	void CalculateNewPosition ();

public:
	void Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fOptional, float fDuration);
	void Stop   (CFXSprite &Sprite, bool bCancel = true);
	void Update (CFXSprite &Sprite);
};

#endif /* CSHAKEEFFECT_HPP_ */
