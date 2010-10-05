/*
 * CSceneManager.hpp
 *
 *  Created on: 25.09.2010
 *      Author: Martu
 */

#ifndef CSCENEMANAGER_HPP_
#define CSCENEMANAGER_HPP_


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Conversation/SCharacter.hpp"
#include "Conversation/SScene.hpp"
#include "Conversation/CTextArea.hpp"
#include "Conversation/CBackground.hpp"

#include <iostream>

class CConversation
{
private:
	sf::RenderWindow *m_pWindow; // our Renderwindow

	// BACKGROUNDVARIABLES //
	CBackground m_Background; // our background

	// CHARACTERS //
	map<int, SCharacter *> *m_pCharacters; // pointer to the character-map

	// PLAYER //
	vector<string> *m_pFlags;  // pointer to the flags for the conditions

	// TEXT LAYER //
	CTextArea *m_pTextArea; // pointer to the TextArea

	// SCENE VARIABLES //
	int   m_CurScene;           // Number of the current Scene // TODO maybe change to a iterator
	float m_fCurrentDuration;   // how long the current scene is running
	bool  m_bChangeBackground;  // if the Background should be changed or not
	vector <SScene> m_Scenes; // Scenes which can be displayed

	// DEFAULT EFFECTS //
	GFXEffect  m_DefaultBGIn;
	GFXEffect  m_DefaultBGOut;

	// GLOBAL VARIABLES //
	bool  m_bHidden;       // If the Textarea and the GUI is hidden or not

	bool ChangeScene (int SceneNr); // change to a specific scene
	bool InFlags     (const string sFlag);

public:
	CConversation  ();
	~CConversation ();

	void Init (sf::RenderWindow *pWindow,
				CTextArea *pTextArea = NULL,
				map<int, SCharacter *> *pCharacters = NULL,
				vector<string> *pFlags = NULL);

	// SETTERS //
	void SetCharacters (map<int, SCharacter *> *pCharacters = NULL);
	void SetFlags      (vector<string> *pFlags = NULL);
	void SetFlag       (string sFlag);
	void SetTextArea   (CTextArea *pTextArea = NULL);
	void SetHidden     (bool bHidden);

	// GETTERS //
	map<int, SCharacter *> *GetCharacters () {return m_pCharacters;};
	vector<string> *GetFlags () {return m_pFlags;};
	CTextArea *GetTextArea () {return m_pTextArea;};
	SScene *GetCurScene () {return &m_Scenes.at (m_CurScene);};
	vector<SScene> *GetScenes () {return &m_Scenes;};
	vector<CChoice *> *GetChoices () {return &m_Scenes.at (m_CurScene).m_Choices;};
	bool IsHidden () {return m_bHidden;};
	bool IsActive ();

	// functions for working with this class
	void DisplayAll ();

	bool LoadScenes (string sPath);
	bool AddScene   (SScene Scene);

	void NextScene ();
	void PrevScene ();
	void GoToScene (int SceneNr);

	void Update ();
	void Render ();
};


#endif /* CSCENEMANAGER_HPP_ */
