/*
 * CFadeEffect.hpp
 *
 *  Created on: 04.09.2010
 *      Author: Martu
 */

#ifndef CFADEEFFECT_HPP_
#define CFADEEFFECT_HPP_

#include "CFXEffect.hpp"

class CFXSprite;

// defines a simple fade effect for a sprite
class CFadeEffect : public CFXEffect
{
private:
	float m_fStartingAlpha;
	float m_fTargetAlpha;
	float m_fCurrentAlpha;
	float m_fDifference;

public:
	void Start  (CFXSprite &Sprite, float fTargetValue, float fDuration);
	void Start  (CFXSprite &Sprite, float fStartingValue, float fTargetValue, float fDuration);
	void Stop   (CFXSprite &Sprite, bool bCancel = true);
	void Update (CFXSprite &Sprite);
};

#endif /* CFADEEFFECT_HPP_ */
