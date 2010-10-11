/*
 * CGame.cpp
 *
 *  Created on: 21.08.2010
 *      Author: Martu
 */

#include "CGame.hpp"

// for description of the Functions see 'CScreen.hpp'

CGame::CGame ()
{
	// Set a standard Background
	//SetBackground ("Backgrounds/Standard.png", sf::Color::Black);

	// Now Load all the characters in the game
	InitCharacters ();

	// Now Initialize our TextArea
	m_TextArea.Init (sf::Vector2f (0, 350), sf::Vector2f (800, 250), "menue.ttf", 15, 0.075f, 0.75f);

	m_TextArea.SetBackgroundSprite("TextArea/Background.png");
	m_TextArea.SetSpeakerPosition (sf::Vector2f (15, 15) );
	m_TextArea.SetTextPosition    (sf::Vector2f (40, 60) );
	m_TextArea.SetTextColor       (sf::Color::Blue, sf::Color::Cyan, sf::Color::Yellow);

	// Now preload the Scenes
	InitScenes ();

	// Now finally Initialize the Gui
	//InitGui ();

	// Initialize the Conversation
	m_Conversation.Init (WINDOW, &m_TextArea, &m_Characters, &m_PlayerFlags);

	m_bHidden       = false;
}

// Destructor, frees memory which isn't needed anymore
CGame::~CGame ()
{
	// first let's release our GUI
	vector<CMenuButton *>::iterator itGUI;
	for (itGUI = m_GuiButtons.begin (); itGUI != m_GuiButtons.end (); itGUI++)
		delete (*itGUI);
	m_GuiButtons.clear ();

	// now the different characters
	map<int, SCharacter *>::iterator itChar;
	for (itChar = m_Characters.begin (); itChar != m_Characters.end (); itChar++)
		delete itChar->second;
	m_Characters.clear ();
}

int CGame::Run ()
{
	// for the moment just delete all player flags
	m_PlayerFlags.clear ();

	bool running = true;

	vector<CChoice *> *pChoices;

	sf::Event Event;
	const sf::Input &Input = WINDOW->GetInput ();
	sf::Vector2f Mouse;

	// for the moment go to the first scene
	m_Conversation.GoToScene (0);

	while (running)
	{
		// Update the Framework
		g_pFramework->Update();

		// get the choices of the current scene
		pChoices = m_Conversation.GetChoices ();

		// get the current position of the mouse, and convert it into the local coordinates
		Mouse = WINDOW->ConvertCoords(Input.GetMouseX (), Input.GetMouseY () );

		// process the Events
		while (WINDOW->GetEvent (Event) )
		{
			if (Event.Type == sf::Event::Closed)
				return CScreen::MAINMENUE; // don't just close. First go back to the MainMenue

			// When F11 is pressed, take a Screenshot
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::F11)
			{
				sf::Image Screenshot = WINDOW->Capture ();
				Screenshot.SaveToFile ("Screenshots/screenshot.png");
			}

			// When left or right is pressed go to the next/previous scene
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Space)
			{
				// but only go to the next scene, when there aren't any choices
				if (pChoices->empty () )
				{
					// test if we're displaying everything
					if (m_Conversation.IsActive () )
						m_Conversation.DisplayAll ();
					else
						m_Conversation.NextScene ();
				}
			}

			// When Backspace is pressed hide or show the Textarea and the gui
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Back)
			{
				// Test if we should hide them or not
				if (m_bHidden)
				{
					// they are hidden, so turn them visible again
					m_Conversation.SetHidden (false);
					m_bHidden = false;
				}
				else
				{
					// they are visible, so hide them
					m_Conversation.SetHidden (true);
					m_bHidden = true;
				}
			}
		}

		// Process the Choices
		if (pChoices->empty () == false)
		{
			vector<CChoice *>::iterator itCH;

			for (itCH = pChoices->begin (); itCH != pChoices->end (); itCH++)
			{
				if ((*itCH)->IsMouseOver (Mouse.x, Mouse.y) )
				{
					(*itCH)->SetMouseOver (true);

					if (Input.IsMouseButtonDown (sf::Mouse::Left) )
					{
						m_Conversation.SetFlag ((*itCH)->GetFlag () );
						m_Conversation.NextScene ();
					}
				}
				else
					(*itCH)->SetMouseOver (false);
			}
		}

		// Process the GUI
		if (m_GuiButtons.empty () == false)
		{
			vector<CMenuButton *>::iterator itGUI;

			for (itGUI = m_GuiButtons.begin (); itGUI != m_GuiButtons.end (); itGUI++)
			{
				if ((*itGUI)->IsMouseOver (Mouse.x, Mouse.y) )
				{
					(*itGUI)->SetState (CButton::MOUSEOVER);

					if (Input.IsMouseButtonDown (sf::Mouse::Left) )
						return (*itGUI)->GetNextScreenID ();
				}
				else
					(*itGUI)->ResetState ();
			}
		}

		// Now Update the Game
		Update ();

		// And now render the whole thing
		Render ();
	}

	// when the Game is over go to the MainMenue
	return CScreen::MAINMENUE; // just for safety should normally never reach this point
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// loads the data for the scenes
void CGame::InitScenes ()
{
	// TODO: actually loading
	// for the moment just define some hardcoded scenes
	// later LOAD them here

	SScene scene1;
	scene1.m_ID = 1;
	scene1.m_bIsRead = false;
	scene1.m_BGColor = sf::Color::Magenta;
	scene1.m_sSpeaker.append ("Martu");
	scene1.m_sText.append ("This should be the first scene ;P");
	scene1.m_fDuration = -1;
	m_Conversation.AddScene (scene1);

	SScene scene2;
	scene2.m_ID = 2;
	scene2.m_bIsRead = false;
	scene2.m_BGColor = sf::Color::Red;
	scene2.m_sSpeaker.append ("Martu");
	scene2.m_sText.append ("This should be the second scene.\nThe Background color should have changed...");
	scene2.m_fDuration = -1;
	m_Conversation.AddScene (scene2);

	SScene scene3;
	scene3.m_ID = 3;
	scene3.m_bIsRead = false;
	scene3.m_BGColor = sf::Color::Black;
	scene3.m_sSpeaker.append ("Martu");
	scene3.m_sText.append ("Except from the text nothing should have changed...\nThe scene has a duration from 15 seconds...\nThe Background has to be handled by the loading function...");
	scene3.m_fDuration = 15;
	m_Conversation.AddScene (scene3);

	SScene scene4;
	scene4.m_ID = 4;
	scene4.m_bIsRead = false;
	scene4.m_BGColor = sf::Color::White;
	scene4.m_BGSprites.push_back ("Backgrounds/Standard.png");
	scene4.m_sSpeaker.append ("Martu");
	scene4.m_sText.append ("Now there should be a Sprite as a Background...");
	scene4.m_fDuration = -1;
	m_Conversation.AddScene (scene4);

	SScene scene5;
	scene5.m_ID = 5;
	scene5.m_bIsRead = false;
	scene5.m_sSpeaker.append ("Martu");
	scene5.m_sText.append ("3 Characters should be onscreen ( I know that the placement is a bit off)");
	scene5.m_fDuration = -1;

	SSceneChar *Schar1;
	Schar1 = new SSceneChar;
	Schar1->m_CharID = 1;
	Schar1->m_Pose = "normal";
	Schar1->m_Position = sf::Vector2f (0,150);
	scene5.m_Characters.push_back (Schar1);

	SSceneChar *Schar2;
	Schar2 = new SSceneChar;
	Schar2->m_CharID = 1;
	Schar2->m_Pose = "surprised";
	Schar2->m_Position = sf::Vector2f (120,150);
	scene5.m_Characters.push_back (Schar2);

	SSceneChar *Schar3;
	Schar3 = new SSceneChar;
	Schar3->m_CharID = 1;
	Schar3->m_Pose = "shocked";
	Schar3->m_Position = sf::Vector2f (600,150);
	scene5.m_Characters.push_back (Schar3);

	m_Conversation.AddScene (scene5);

	SScene scene6;
	scene6.m_ID = 6;
	scene6.m_bIsRead = false;
	scene6.m_sSpeaker.append ("Martu");
	scene6.m_sText.append ("2 Questions should be visible, choose wisely 0o");
	scene6.m_fDuration = -1;

	CChoice *choice1;
	choice1 = new CChoice;
	choice1->Init ("choice.png", sf::Vector2i (200, 106) );
	choice1->m_ButtonSprite.SetPosition (300, 150);
	choice1->SetFont ("menue.ttf");
	choice1->SetChoice ("CLICK ME :O", "CHOICE1");
	scene6.m_Choices.push_back (choice1);

	CChoice *choice2;
	choice2 = new CChoice;
	choice2->Init ("choice.png", sf::Vector2i (200, 106) );
	choice2->m_ButtonSprite.SetPosition (300, 325);
	choice2->SetFont ("menue.ttf");
	choice2->SetChoice ("NO get Me... I'll make you happy ;O", "CHOICE2");
	scene6.m_Choices.push_back (choice2);

	m_Conversation.AddScene (scene6);

	SScene scene7;
	scene7.m_ID = 7;
	scene7.m_bIsRead = false;
	scene7.m_sSpeaker.append ("Normal guy");
	scene7.m_sText.append ("Thanks that you pressed the upper button...\nI'm really glad that you did it\nREALLY...");
	scene7.m_fDuration = -1;
	SSceneConditions *cond1;
	cond1 = new SSceneConditions;
	cond1->m_ConditionType = SSceneConditions::INCLUDES;
	cond1->m_Condition.append ("CHOICE1");
	scene7.m_Conditions.push_back (cond1);

	SSceneChar *Schar4;
	Schar4 = new SSceneChar;
	Schar4->m_CharID = 1;
	Schar4->m_Pose = "normal";
	Schar4->m_Position = sf::Vector2f (240,150);
	scene7.m_Characters.push_back (Schar4);

	m_Conversation.AddScene (scene7);

	SScene scene8;
	scene8.m_ID = 8;
	scene8.m_bIsRead = false;
	scene8.m_sSpeaker.append ("Shocked guy");
	scene8.m_sText.append ("wait WHAT 0o\nDON'T BELIEVE HIM!\nHe's trying to trick you, really...");
	scene8.m_fDuration = -1;
	SSceneConditions *cond2;
	cond2 = new SSceneConditions;
	cond2->m_ConditionType = SSceneConditions::INCLUDES;
	cond2->m_Condition.append ("CHOICE1");
	scene8.m_Conditions.push_back (cond2);

	SSceneChar *Schar5;
	Schar5 = new SSceneChar;
	Schar5->m_CharID = 1;
	Schar5->m_Pose = "normal";
	Schar5->m_Position = sf::Vector2f (140,150);
	scene8.m_Characters.push_back (Schar5);

	SSceneChar *Schar6;
	Schar6 = new SSceneChar;
	Schar6->m_CharID = 1;
	Schar6->m_Pose = "shocked";
	Schar6->m_Position = sf::Vector2f (340,150);
	scene8.m_Characters.push_back (Schar6);

	m_Conversation.AddScene (scene8);

	SScene scene9;
	scene9.m_ID = 9;
	scene9.m_bIsRead = false;
	scene9.m_sSpeaker.append ("Surprised guy");
	scene9.m_sText.append ("Whoaaa you really clicked me...\nThat turns me really on and makes me happy\nyou know what?\nI LOVE YOU");
	scene9.m_fDuration = -1;
	SSceneConditions *cond3;
	cond3 = new SSceneConditions;
	cond3->m_ConditionType = SSceneConditions::INCLUDES;
	cond3->m_Condition.append ("CHOICE2");

	SSceneConditions *cond4; // OPTIONAL just for testing
	cond4 = new SSceneConditions;
	cond4->m_ConditionType = SSceneConditions::NOTINCLUDES;
	cond4->m_Condition.append ("CHOICE1");
	scene9.m_Conditions.push_back (cond3);
	scene9.m_Conditions.push_back (cond4);

	SSceneChar *Schar7;
	Schar7 = new SSceneChar;
	Schar7->m_CharID = 1;
	Schar7->m_Pose = "surprised";
	Schar7->m_Position = sf::Vector2f (240,150);
	scene9.m_Characters.push_back (Schar7);

	m_Conversation.AddScene (scene9);

	SScene scene10;
	scene10.m_ID = 10;
	scene10.m_bIsRead = false;
	scene10.m_sSpeaker.append ("All Together");
	scene10.m_sText.append ("OK that was just a test if the choices are working\n or at least I hope\nit was a test ... 0o");
	scene10.m_fDuration = -1;

	SSceneChar *Schar8;
	Schar8 = new SSceneChar;
	Schar8->m_CharID = 1;
	Schar8->m_Pose = "normal";
	Schar8->m_Position = sf::Vector2f (0,150);
	scene10.m_Characters.push_back (Schar8);

	SSceneChar *Schar9;
	Schar9 = new SSceneChar;
	Schar9->m_CharID = 1;
	Schar9->m_Pose = "surprised";
	Schar9->m_Position = sf::Vector2f (240,150);
	scene10.m_Characters.push_back (Schar9);

	SSceneChar *Schar10;
	Schar10 = new SSceneChar;
	Schar10->m_CharID = 1;
	Schar10->m_Pose = "shocked";
	Schar10->m_Position = sf::Vector2f (600,150);
	scene10.m_Characters.push_back (Schar10);

	m_Conversation.AddScene (scene10);

	SScene scene11;
	scene11.m_ID = 11;
	scene11.m_bIsRead = false;
	scene11.m_sSpeaker.append ("All Together");
	scene11.m_sText.append ("Now let's test if the same character can\nappear multiples times on the screen.");
	scene11.m_fDuration = -1;

	SSceneChar *Schar11;
	Schar11 = new SSceneChar;
	Schar11->m_CharID = 1;
	Schar11->m_Pose = "normal";
	Schar11->m_Position = sf::Vector2f (0,150);
	scene11.m_Characters.push_back (Schar1);

	SSceneChar *Schar12;
	Schar12 = new SSceneChar;
	Schar12->m_CharID = 1;
	Schar12->m_Pose = "normal";
	Schar12->m_Position = sf::Vector2f (300,150);
	scene11.m_Characters.push_back (Schar12);

	SSceneChar *Schar13;
	Schar13 = new SSceneChar;
	Schar13->m_CharID = 1;
	Schar13->m_Pose = "shocked";
	Schar13->m_Position = sf::Vector2f (240,150);
	scene11.m_Characters.push_back (Schar13);

	m_Conversation.AddScene (scene11);

	SScene scene12;
	scene12.m_ID = 12;
	scene12.m_bIsRead = false;
	scene12.m_sSpeaker.append ("All Together");
	scene12.m_sText.append ("scenefading test...\nThe Character on the right side and the one in the middle should be faded-out and the faded-in again... (not implemented yet)");
	scene12.m_fDuration = -1;

	SSceneChar *Schar14;
	Schar14 = new SSceneChar;
	Schar14->m_CharID = 1;
	Schar14->m_Pose = "normal";
	Schar14->m_Position = sf::Vector2f (0,150);
	scene12.m_Characters.push_back (Schar14);

	SSceneChar *Schar15;
	Schar15 = new SSceneChar;
	Schar15->m_CharID = 1;
	Schar15->m_Pose = "surprised";
	Schar15->m_Position = sf::Vector2f (300,150);
	scene12.m_Characters.push_back (Schar15);

	SSceneChar *Schar16;
	Schar16 = new SSceneChar;
	Schar16->m_CharID = 1;
	Schar16->m_Pose = "shocked";
	Schar16->m_Position = sf::Vector2f (260,200);
	scene12.m_Characters.push_back (Schar16);

	m_Conversation.AddScene (scene12);

	SScene scene13;
	scene13.m_ID = 13;
	scene13.m_bIsRead = false;
	scene13.m_BGColor = sf::Color::Black;
	scene13.m_sSpeaker.append ("Martu");
	scene13.m_sText.append ("Ok now let's test some of the Background effects (No Characters, because I'm just too lazy at the moment ^^)\nThen let's begin with the uhhm...    \nFadeEffect ;P");
	scene13.m_fDuration = -1;

	GFXEffect *fx1;
	fx1 = new GFXEffect;
	fx1->m_Type = GFXEffect::FADE;
	fx1->m_fStartingValue = 255;
	fx1->m_fTargetValue   = 90;
	fx1->m_fDuration      = 2.5;
	scene13.m_Effects.push_back (fx1);

	m_Conversation.AddScene (scene13);

	SScene scene14;
	scene14.m_ID = 14;
	scene14.m_bIsRead = false;
	scene14.m_sSpeaker.append ("");
	scene14.m_sText.append ("");
	scene14.m_fDuration = 0.5;

	GFXEffect *fx2;
	fx2 = new GFXEffect;
	fx2->m_Type = GFXEffect::SHAKE;
	fx2->m_TargetValue = sf::Vector2f (0, 40);
	fx2->m_fOptional   = 0.05;
	fx2->m_fDuration   = 0.3;
	scene14.m_Effects.push_back (fx2);

	m_Conversation.AddScene (scene14);

	SScene scene15;
	scene15.m_ID = 15;
	scene15.m_bIsRead = false;
	scene15.m_sSpeaker.append ("Martu");
	scene15.m_sText.append ("Ouch!        \nDamn step...  \nAnyway, now I knwo that the shaking is working too ;P");
	scene15.m_fDuration = -1;
	m_Conversation.AddScene (scene15);

	SScene scene16;
	scene16.m_ID = 16;
	scene16.m_bIsRead = false;
	scene16.m_sSpeaker.append ("Martu");
	scene16.m_sText.append ("Now Please look very closely\n          \nAnd found anything?   \nNothing?     \nI'd be surprised ;P");
	scene16.m_fDuration = -1;

	GFXEffect *fx3;
	fx3 = new GFXEffect;
	fx3->m_Type = GFXEffect::ZOOM;
	fx3->m_StartingValue = sf::Vector2f (1, 1);
	fx3->m_TargetValue   = sf::Vector2f (3.25, 3.25);
	fx3->m_fDuration     = 5;
	scene16.m_Effects.push_back (fx3);

	GFXEffect *fx33;
	fx33 = new GFXEffect;
	fx33->m_Type = GFXEffect::FADE;
	fx33->m_fStartingValue = 90;
	fx33->m_fTargetValue   = 255;
	fx33->m_fDuration      = 0.5;
	scene16.m_Effects.push_back (fx33);

	m_Conversation.AddScene (scene16);

	SScene scene17;
	scene17.m_ID = 17;
	scene17.m_bIsRead = false;
	scene17.m_BGSprites.push_back ("Backgrounds/panorama.jpg");
	scene17.m_sSpeaker.append ("Martu");
	scene17.m_sText.append ("Woaaahhh...        \nWhat a beautiful view      \nAmazing.");
	scene17.m_fDuration = -1;

	GFXEffect *fx4;
	fx4 = new GFXEffect;
	fx4->m_Type = GFXEffect::SCROLL;
	fx4->m_StartingValue = sf::Vector2f (0, 0);
	fx4->m_TargetValue   = sf::Vector2f (6901, 0);
	fx4->m_Size          = sf::Vector2f (800,600);
	fx4->m_fDuration     = 15;
	scene17.m_Effects.push_back (fx4);

	m_Conversation.AddScene (scene17);

	SScene scene18;
	scene18.m_ID = 18;
	scene18.m_bIsRead = false;
	scene18.m_BGSprites.push_back ("Backgrounds/Standard.png");
	scene18.m_sSpeaker.append ("Martu");
	scene18.m_sText.append ("huh whats going on now 0o \nHELP everythings gone crazy 0o \nHELP ME waaaaahhhh... \n\n*DEAD*");
	scene18.m_fDuration = -1;

	GFXEffect *fx5;
	fx5 = new GFXEffect;
	fx5->m_Type = GFXEffect::ZOOM;
	fx5->m_StartingValue = sf::Vector2f (1, 1);
	fx5->m_TargetValue   = sf::Vector2f (2, 3.25);
	fx5->m_fDuration     = 7;
	scene18.m_Effects.push_back (fx5);

	GFXEffect *fx6;
	fx6 = new GFXEffect;
	fx6->m_Type = GFXEffect::SHAKE;
	fx6->m_TargetValue = sf::Vector2f (125, 125);
	fx6->m_fOptional   = 0.1;
	fx6->m_fDuration   = 7;
	scene18.m_Effects.push_back (fx6);

	GFXEffect *fx7;
	fx7 = new GFXEffect;
	fx7->m_Type = GFXEffect::FADE;
	fx7->m_fStartingValue = 255;
	fx7->m_fTargetValue   = 0;
	fx7->m_fDuration      = 7;
	scene18.m_Effects.push_back (fx7);

	m_Conversation.AddScene (scene18);
}

// Loads the characters
void CGame::InitCharacters ()
{
	// and now load the characters
	// TODO actually load something

	SCharacter *Char;
	Char = new SCharacter;
	Char->m_ID = 1;
	Char->m_sName.append ("testing");
	Char->m_Sprites.AddImage ("normal", "characters/testing_normal.png");
	Char->m_Sprites.AddImage ("surprised", "characters/testing_surprised.png");
	Char->m_Sprites.AddImage ("shocked", "characters/testing_shocked.png");
	Char->m_Sprites.SetCenter (sf::Vector2f (150,150)); // TODO every image needs its own center/scale/...
	m_Characters[Char->m_ID] = Char;
}

//TODO: void CGame::InitGui ();

void CGame::Update ()
{
	// Update the Conversation
	m_Conversation.Update ();
}

void CGame::Render ()
{
	// clear the window first
	WINDOW->Clear ();

	// draw the conversation
	m_Conversation.Render ();

	// And now comes the GUI
	vector<CMenuButton *>::iterator it;
	for (it  = m_GuiButtons.begin (); it != m_GuiButtons.end (); it++)
	{
		WINDOW->Draw ((*it)->m_ButtonSprite);
	}

	g_pFramework->Render ();
}
