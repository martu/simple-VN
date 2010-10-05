/*
 * CFXSprite.hpp
 *
 *  Created on: 04.09.2010
 *      Author: Martu
 */

#ifndef CFXSPRITE_HPP_
#define CFXSPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "GFXEffects.hpp"

using namespace std;

// class for easily adding effects to a sprite
class CFXSprite : public sf::Sprite
{
protected:
	vector<CFXEffect *> m_Effects; // Effects applied to this Sprite

public:
	virtual ~CFXSprite ();
	void AddEffect    (CFXEffect *effect);
	void ClearEffects ();
	vector<CFXEffect *> &GetEffects ();
	CFXEffect *GetEffect (int EffectID);
	CFXEffect *GetLastEffect ();

	virtual void Update ();
	virtual bool IsActive ();
};

// combines all the necessary variables for every possible effect
struct GFXEffect
{
	enum TYPES
	{
		PRESERVE, // not really a effect, but may be useful for some things
		STOPALL,  // Stops every currently running effect
		FADE,
		ZOOM,
		SHAKE,
		SCROLL
	};

	TYPES  m_Type; // ID of the effect
	float  m_fDuration; // the duration of the effect
	float  m_fDelay;    // the delay befor the effect starts
	bool   m_bSetToTarget; // if the effect should be set to the target value when stopped

	float m_fTargetValue;
	sf::Vector2f m_TargetValue;

	float m_fStartingValue;
	sf::Vector2f m_StartingValue;

	float m_fOptional;
	sf::Vector2f m_Size;
};

// Helper Functions USING THE NAMESPACE GFX
namespace GFX
{
	void SetEffect (CFXSprite &Sprite, GFXEffect &Effect);
} // GFX

#endif /* CFXSPRITE_HPP_ */
