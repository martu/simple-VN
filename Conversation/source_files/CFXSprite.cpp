/*
 * CFXSprite.cpp
 *
 *  Created on: 04.09.2010
 *      Author: Martu
 */

#include "Conversation/CFXSprite.hpp"

CFXSprite::~CFXSprite ()
{
	vector<CFXEffect *>::iterator it;
	for (it = m_Effects.begin (); it != m_Effects.end (); it++)
		delete (*it);
}

// Adds the Effect to the effect-list
void CFXSprite::AddEffect    (CFXEffect *effect)
{
	m_Effects.push_back (effect);
}

// deletes every effect from the Sprite
void CFXSprite::ClearEffects ()
{
	vector<CFXEffect *>::iterator it;
	for (it = m_Effects.begin (); it != m_Effects.end (); it++)
		delete (*it);

	m_Effects.clear ();
}

// returns a reference to the effect list
vector<CFXEffect *> &CFXSprite::GetEffects ()
{
	return m_Effects;
}

// returns the effect at the given ID
CFXEffect *CFXSprite::GetEffect (int EffectID)
{
	// test if the ID is valid
	if (EffectID < 0 || EffectID > static_cast<int> (m_Effects.size ())  - 1)
		return NULL;
	else
		return m_Effects[EffectID];
}

// returns the last added effect
CFXEffect *CFXSprite::GetLastEffect ()
{
	return m_Effects[m_Effects.size () - 1];
}

// Update every effect in the list
void CFXSprite::Update ()
{
	vector<CFXEffect *>::iterator it;
	for (it = m_Effects.begin (); it != m_Effects.end (); it++)
		(*it)->Update (*this);
}

// returns true if one effect is still active
bool CFXSprite::IsActive ()
{
	vector<CFXEffect *>::iterator it;
	for (it = m_Effects.begin (); it != m_Effects.end (); it++)
	{
		// if at least one effect is still active it will return true
		if ((*it)->IsActive () )
			return true;
	}

	return false;
}

/////////////////////////////////////////
//          HELPER FUNCTIONS           //
/////////////////////////////////////////

// Sets the effect for the given sprite
void GFX::SetEffect (CFXSprite &Sprite, GFXEffect &Effect)
{
	// now check what effect this is
	switch (Effect.m_Type)
	{
		case GFXEffect::PRESERVE:
		{
			// nothing to do here
		}break;
		case GFXEffect::STOPALL:
		{
			vector<CFXEffect *> *tmp = &Sprite.GetEffects ();
			vector<CFXEffect *>::iterator it;

			for (it = tmp->begin (); it != tmp->end (); it++)
			{
				if (Effect.m_bSetToTarget)
				{
					(*it)->SetToTarget ();
					(*it)->Update (Sprite); // don't forget to update them one last time
				}

				(*it)->Stop (Sprite, false);
			}

			Sprite.ClearEffects ();
		}break;
		case GFXEffect::FADE:
		{
			// we have a fade effect, so set the effect
			Sprite.AddEffect     (new CFadeEffect);
			Sprite.GetLastEffect ()->Start (Sprite,
											Effect.m_fStartingValue,
											Effect.m_fTargetValue,
											Effect.m_fDuration);

			Sprite.GetLastEffect ()->SetDelay (Effect.m_fDelay);
		}break;
		case GFXEffect::ZOOM:
		{
			// ok add a zoom effect
			Sprite.AddEffect     (new CZoomEffect);
			Sprite.GetLastEffect ()->Start (Sprite,
											Effect.m_StartingValue,
											Effect.m_TargetValue,
											Effect.m_fDuration);

			Sprite.GetLastEffect ()->SetDelay (Effect.m_fDelay);
		}break;
		case GFXEffect::SHAKE:
		{
			// add some shake effect
			Sprite.AddEffect     (new CShakeEffect);
			Sprite.GetLastEffect ()->Start (Sprite,
											Effect.m_TargetValue,
											Effect.m_fOptional,
											Effect.m_fDuration);

			Sprite.GetLastEffect ()->SetDelay (Effect.m_fDelay);
		}break;
		case GFXEffect::SCROLL:
		{
			// and the code for a scroll effect
			Sprite.AddEffect     (new CScrollEffect);
			Sprite.GetLastEffect ()->Start (Sprite,
											Effect.m_StartingValue,
											Effect.m_TargetValue,
											Effect.m_fDuration);

			Sprite.GetLastEffect ()->SetDelay (Effect.m_fDelay);
			Sprite.GetLastEffect ()->SetSize ( Effect.m_Size);
		}break;
	}
}

