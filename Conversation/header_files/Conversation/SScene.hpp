/*
 * SScene.hpp
 *
 *  Created on: 25.08.2010
 *      Author: Martu
 */

#ifndef SSCENE_HPP_
#define SSCENE_HPP_

#include "CChoice.hpp"
#include "SCharacter.hpp"

// struct which describes one character for the scene
// we can't use the character struct here directly because then we could only have
// one instance for a character. With this struct we can have the same character
// multiple times on the screen with different positions and poses
struct SSceneChar
{
	int m_CharID; // the ID of the character
	string m_Pose;   // the number of the pose
	sf::Vector2f m_Position; // Position of this character
};

// defines different types of conditions for one scene
struct SSceneConditions
{
	enum TYPES
	{
		INCLUDES,    // Player includes the following flag
		NOTINCLUDES, // Player does NOT include the following flag
		SCENE,       // use the Condition from the following SceneID
	};

	TYPES  m_ConditionType;
	string m_Condition;
};

// describes the needed information for one scene.
// one scene is one screen with the text, characters, ...
struct SScene
{
	// Variables with the comment "OPTIONAL" just need to be there when they should change
	int       m_ID;
	bool      m_bIsRead;   // If the Text was once displayed or not (decides text color)
	string    m_sSpeaker;  // speaker of the Text
	string    m_sText;     // Text for this scene

	float     m_fDuration; // OPTIONAL used when the scene should change after some given time
	sf::Color m_BGColor;   // OPTIONAL
	vector<SSceneChar *> m_Characters; // OPTIONAL Characters in this scene
	vector<string> m_BGSprites; // OPTIONAL path to the Image used for the Background
	vector<CChoice *> m_Choices; // OPTIONAL Buttons when the scene should include choices
	vector<SSceneConditions *> m_Conditions; // OPTIONAL when this scene should only be used when certain flags are set
	vector<GFXEffect *> m_Effects; // OPTIONAL when this scene should use effects
};


#endif /* SSCENE_HPP_ */
