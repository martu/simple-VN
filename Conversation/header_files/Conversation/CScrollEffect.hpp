/*
 * CScrollEffect.hpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#ifndef CSCROLLEFFECT_HPP_
#define CSCROLLEFFECT_HPP_

#include "CFXEffect.hpp"

class CFXSprite;

// defines a simple fade effect for a sprite
class CScrollEffect : public CFXEffect
{
private:
	sf::Vector2f m_StartingPosition;
	sf::Vector2f m_TargetPosition;
	sf::Vector2f m_CurrentPosition;
	sf::Vector2f m_Difference;
	sf::Vector2f m_SpriteSize;
	sf::Vector2f m_Size;

	sf::IntRect  m_StartingRect;

	bool m_bCalculated;

	void CalculateTarget ();

public:
	void Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fDuration);
	void Start  (CFXSprite &Sprite, sf::Vector2f StartingValue, sf::Vector2f TargetValue, float fDuration);

	void SetSize (sf::Vector2f Size);

	void Stop   (CFXSprite &Sprite, bool bCancel = true);
	void Update (CFXSprite &Sprite);
};

#endif /* CSCROLLEFFECT_HPP_ */
