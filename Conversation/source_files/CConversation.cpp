/*
 * CSceneManager.cpp
 *
 *  Created on: 25.09.2010
 *      Author: Martu
 */

#include "CConversation.hpp"

CConversation::CConversation  ()
{
	// Set every pointer to NULL
	m_pWindow     = NULL;
	m_pCharacters = NULL;
	m_pFlags      = NULL;
	m_pTextArea   = NULL;
}

CConversation::~CConversation ()
{
	// the only save thing we can do here is to delete the scenes
	// we can't delete the characters/textarea/flags/renderwindow here, because all of them
	// are passed as pointers to this class, so we may end up deleting still important stuff for the game

	m_Scenes.clear ();
}

// Initialize a conversation. When NULL is being passed create some standard objects for them
void CConversation::Init (sf::RenderWindow *pWindow,
			CTextArea *pTextArea,
			map<int, SCharacter *> *pCharacters,
			vector<string> *pFlags)
{
	m_pWindow = pWindow;

	SetTextArea (pTextArea);
	SetCharacters (pCharacters);
	SetFlags (pFlags);
	SetHidden (false);

	// initialize the background
	m_Background.Init (m_pWindow);

	// Define the Default effects
	m_DefaultBGIn.m_Type = GFXEffect::FADE; // Fade the scenes in
	m_DefaultBGIn.m_fStartingValue = 0;
	m_DefaultBGIn.m_fTargetValue   = 255;
	m_DefaultBGIn.m_fDuration      = 1;

	m_DefaultBGOut.m_Type = GFXEffect::FADE; // Fade the scenes out
	m_DefaultBGOut.m_fStartingValue = 255;
	m_DefaultBGOut.m_fTargetValue   = 0;
	m_DefaultBGOut.m_fDuration      = 1;

	// Go to the first scene
	m_CurScene = 0;
}

// SETTERS // When one of them is given NULL, create a standard object for it
void CConversation::SetCharacters (map<int, SCharacter *> *pCharacters)
{
	if (pCharacters == NULL)
	{
		// create some empty array
		// POSSIBLE MEMORY LEAK because we don't properly delete the old one (reason see the destructor)
		m_pCharacters = new map<int, SCharacter *>;
	}
	else
		m_pCharacters = pCharacters;
}

void CConversation::SetFlags      (vector<string> *pFlags)
{
	if (pFlags == NULL)
	{
		// create an empty array of flags
		m_pFlags = new vector<string>;
	}
	else
		m_pFlags = pFlags;
}

void CConversation::SetFlag (string sFlag)
{
	// first test if the Flag is already set
	if (InFlags (sFlag) )
		return; // the flag is already set, so we have nothing to do
	else
		m_pFlags->push_back (sFlag); // the flags isn't set, so set it
}

void CConversation::SetTextArea   (CTextArea *pTextArea)
{
	if (pTextArea == NULL)
	{
		// create a standard TextArea
		m_pTextArea = new CTextArea;

		// I assume that this class was Initialized and we have the pointer to the renderwindow
		// otherwise this will crash the programm
		m_pTextArea->Init (sf::Vector2f (15, 15),
						   sf::Vector2f (m_pWindow->GetWidth ()-30, m_pWindow->GetHeight ()-30 ),
						   "DEFAULT",
						   30,
						   0.075f,
						   0.75f);

		m_pTextArea->SetBackgroundColor (sf::Color (60, 180, 60) );
		m_pTextArea->SetSpeakerPosition (sf::Vector2f (15, 15) );
		m_pTextArea->SetTextPosition    (sf::Vector2f (40, 60) );
		m_pTextArea->SetTextColor       (sf::Color::Blue, sf::Color::Cyan, sf::Color::Yellow);
	}
	else
		m_pTextArea = pTextArea;
}

void CConversation::SetHidden     (bool bHidden)
{
	m_bHidden = bHidden;

	// check if we should hide or show the textarea
	if (m_bHidden) // TODO not only fading but every effect should be possible
		m_pTextArea->SetFade (255, 0, 1);
	else
		m_pTextArea->SetFade (0, 255, 1);
}

bool CConversation::IsActive ()
{
	if (m_pTextArea->IsActive () || m_Background.IsActive () )
		return true;
	else
		return false;
}

void CConversation::DisplayAll ()
{
	// display the complete text
	m_pTextArea->DisplayAll ();

	// and stop every effect on the background
	m_Background.StopEffects (true);
}

bool CConversation::LoadScenes (string sPath)
{
	// TODO LOAD SOMETHING

	return true;
}

bool CConversation::AddScene   (SScene Scene)
{
	m_Scenes.push_back (Scene);

	return true;
}

void CConversation::NextScene ()
{
	bool ChangedTheScene = false;
	unsigned int  Scene = m_CurScene;

	while (ChangedTheScene == false)
	{
		Scene++;

		// test if this would be a valid scene
		if (Scene < m_Scenes.size () )
			ChangedTheScene = ChangeScene (Scene); // is valid, so try to change it
		else
			ChangedTheScene = true; // not valid, so change nothing but get out of the while
	}
}

void CConversation::PrevScene ()
{
	bool ChangedTheScene = false;
	unsigned int  Scene = m_CurScene;

	while (ChangedTheScene == false)
	{
		Scene--;

		// test if this would be a valid scene
		if (Scene >= 0)
			ChangedTheScene = ChangeScene (Scene); // valid so try to change it
		else
			ChangedTheScene = true; // not valid, so change nothing but get out of the while
	}
}

void CConversation::GoToScene (unsigned int SceneNr)
{
	// go to a specific scene

	// the test if this is a valid scene is done by the ChangeScene-function
	ChangeScene (SceneNr);
}

void CConversation::Update ()
{
	m_fCurrentDuration += m_pWindow->GetFrameTime ();

	// Update every sprite
	m_Background.Update ();

	// Update the TextArea
	m_pTextArea->Update (m_pWindow->GetFrameTime () );

	// Check if the current scene has a maximum duration
	if (m_Scenes.at (m_CurScene).m_fDuration >= 0 &&
		m_Scenes.at (m_CurScene).m_fDuration <= m_fCurrentDuration &&
		m_Scenes.at (m_CurScene).m_Choices.empty () )
		NextScene (); // Go to the Next scene
}

void CConversation::Render ()
{
	m_Background.Render ();

	// Secondly render the characters of the current scene
	vector<SSceneChar *>::iterator itC;
	for (itC  = m_Scenes.at (m_CurScene).m_Characters.begin ();
		 itC != m_Scenes.at (m_CurScene).m_Characters.end ();
		 itC++)
	{
		m_pCharacters->find ((*itC)->m_CharID)->second->m_Sprites.SetPosition ((*itC)->m_Position);
		m_pWindow->Draw (*m_pCharacters->find ((*itC)->m_CharID)->second->m_Sprites.GetImage ((*itC)->m_Pose) );
	}

	// Now render the choices of the current scene
	vector<CChoice *>::iterator itChoice;
	for (itChoice  = m_Scenes.at (m_CurScene).m_Choices.begin ();
		 itChoice != m_Scenes.at (m_CurScene).m_Choices.end ();
		 itChoice++)
	{
		(*itChoice)->Render (m_pWindow);
	}

	// Finally render the TextArea
	m_pTextArea->Render (m_pWindow);
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// change to a specific scene
bool CConversation::ChangeScene (unsigned int SceneNr)
{
	// for safety test if this is a valid scene
	if (SceneNr >= m_Scenes.size () )
		return false;

	// we're still here so this is a valid number

	bool bConditionsMet   = true;
	SScene *tmp = &m_Scenes.at (SceneNr);

	std::cout << "-1 < " << SceneNr << " < " << m_Scenes.size () << std::endl;

	// check if the next scene has any condition
	if (tmp->m_Conditions.empty() == false)
	{
		std::cout << "The Next scene has some Conditions" << std::endl;
		// checking if the condition for the scene are met, otherwise test the next
		// one until we found a scene or we don't have anymore scenes
		vector<SSceneConditions *>::iterator it;
		for (it = tmp->m_Conditions.begin (); it != tmp->m_Conditions.end (); it++)
		{
			// check what type of condition this scene has
			// the Condition-Type "SCENE" is handled by the Scene-loading function
			switch ((*it)->m_ConditionType)
			{
				case SSceneConditions::INCLUDES:
				{
					std::cout << "The Condition is: INCLUDE " << (*it)->m_Condition;
					if (InFlags ((*it)->m_Condition) == false)
					{
						std::cout << " FALSE" << std::endl;
						bConditionsMet = false;
					}
					else
						std::cout << " TRUE" << std::endl;
				}break;
				case SSceneConditions::NOTINCLUDES:
				{
					std::cout << "The Condition is: DOES NOT INCLUDE " << (*it)->m_Condition;
					if (InFlags ((*it)->m_Condition) == true)
					{
						std::cout << " FALSE" << std::endl;
						bConditionsMet = false;
					}
					else
						std::cout << " TRUE" << std::endl;
				}break;
				case SSceneConditions::SCENE:
				{
					// is handled by the scene loading function.
					// this here is just that a warning isn't shown
				}break;
			}
		}
	}

	if (bConditionsMet)
	{
		std::cout << "The conditions were met" << std::endl;
		m_CurScene = SceneNr;

		// clear the old backgrounds and replace them with the "new" ones
		m_Background.Swap ();

		// Set the new Background
		m_Background.SetBackgroundColor (tmp->m_BGColor);
		vector<string>::iterator itBGSprite;
		for (itBGSprite = tmp->m_BGSprites.begin ();
			 itBGSprite != tmp->m_BGSprites.end   ();
			 itBGSprite++)
			m_Background.SetBackgroundSprite ((*itBGSprite));

		// Set the transitions if needed
		m_Background.SetTransition (&m_DefaultBGIn, &m_DefaultBGOut); // TODO currently only the default effects

		// Set the new Text
		m_pTextArea->SetText (tmp->m_sSpeaker, tmp->m_sText, tmp->m_bIsRead);

		// Now that the text was/is displayed, it was read
		tmp->m_bIsRead = true;

		// now check if this scene has effects
		if (!tmp->m_Effects.empty () )
		{
			// ok we have some effects, so apply them
			vector<GFXEffect *>::iterator itEffect;
			for (itEffect = tmp->m_Effects.begin (); itEffect != tmp->m_Effects.end (); itEffect++)
				m_Background.SetEffect ( (*itEffect) );
		}

		// Reset the current duration
		m_fCurrentDuration = 0.0f;
	}
	else
		return false; // the conditions weren't met

	return true;
}

bool CConversation::InFlags (const string sFlag)
{
	vector<string>::iterator it;
	for (it = m_pFlags->begin (); it != m_pFlags->end (); it++)
	{
		if ((*it).compare (sFlag) == 0)
			return true;
	}

	// If we're still here, nothing has been found
	return false;
}
