/*
 * SCharacter.hpp
 *
 *  Created on: 25.08.2010
 *      Author: Martu
 */

#ifndef SCHARACTER_HPP_
#define SCHARACTER_HPP_

#include "CImageSequence.hpp"

// struct for defining one character of the game
struct SCharacter
{
	int            m_ID;       // Unique ID for the Character
	string         m_sName;    // Name of the Character
	CImageSequence m_Sprites;  // Sprites for the Character
};

#endif /* SCHARACTER_HPP_ */
