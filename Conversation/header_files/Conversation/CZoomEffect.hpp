/*
 * CZoomEffect.hpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#ifndef CZOOMEFFECT_HPP_
#define CZOOMEFFECT_HPP_

#include "CFXEffect.hpp"

class CFXSprite;

// defines a simple fade effect for a sprite
class CZoomEffect : public CFXEffect
{
private:
	sf::Vector2f m_StartingScale;
	sf::Vector2f m_TargetScale;
	sf::Vector2f m_CurrentScale;
	sf::Vector2f m_Difference;

public:
	void Start  (CFXSprite &Sprite, sf::Vector2f TargetValue, float fDuration);
	void Start  (CFXSprite &Sprite, sf::Vector2f StartingValue, sf::Vector2f TargetValue, float fDuration);
	void Stop   (CFXSprite &Sprite, bool bCancel = true);
	void Update (CFXSprite &Sprite);
};

#endif /* CZOOMEFFECT_HPP_ */
