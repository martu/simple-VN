/*
 * CIntro.hpp
 *
 *  Created on: 22.07.2010
 *      Author: Martu
 */

#ifndef CINTRO_HPP_
#define CINTRO_HPP_

#include "CScreen.hpp"
#include "Conversation/CFXSprite.hpp"

// Screen for showing an Intro
class CIntro : public CScreen
{
private:
	bool m_bEffectSet;

	vector<string>    m_SpritePaths; // Paths to the sprites (used for releasing them)

	bool Fade (CFXSprite *tmp, float from, float to, float duration);

public:
	CIntro ();
	void SetSprite (string path);
	int Run ();
};

#endif /* CINTRO_HPP_ */
