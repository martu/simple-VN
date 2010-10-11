/*
 * CGame.hpp
 *
 *  Created on: 21.08.2010
 *      Author: Martu
 */

#ifndef CGAME_HPP_
#define CGAME_HPP_

#include "CScreen.hpp"
#include "CConversation.hpp"
#include "CMenuButton.hpp"
#include <map>

// the main game class. here runs the actual game
class CGame : public CScreen
{
private:
	// CHARACTERS //
	map<int, SCharacter *> m_Characters; // vector of all characters in the game

	// PLAYER //
	vector<string> m_PlayerFlags;  // Flags from the player

	// TextArea //
	CTextArea m_TextArea; // Area which displays the Text, used in the conversation

	// CONVERSATION //
	CConversation m_Conversation;

	// GUI //
	vector<CMenuButton *> m_GuiButtons; // Buttons for the Gui

	// GLOBAL VARIABLES //
	bool  m_bHidden;       // If the Textarea and the GUI is hidden or not

	// PRIVATE FUNCTIONS //
	void InitScenes (); //Loads the Scenes (ONLY the Data, NOT the actual Images and so on)
	void InitCharacters (); // Loads the characters
	void InitGui ();    // Initializes the Gui
	void Update ();
	void Render ();

public:
	CGame ();
	~CGame ();
	int Run ();
};

#endif /* CGAME_HPP_ */
