/*
 * CMainmenue.cpp
 *
 *  Created on: 04.08.2010
 *      Author: Martu
 */

#include "CMainmenue.hpp"

// for description of the Functions see 'CScreen.hpp'

CMainMenue::CMainMenue ()
{
	m_BGSprite.SetImage (g_pImageManager->getImage("Mainmenue/Background.png") );

	// Initialize the Buttons
	CMenuButton *tmpbutton;
	tmpbutton = new CMenuButton;
	tmpbutton->Init("Start_Game.png", sf::Vector2i (100,50), CButton::ACTIVATED);
	tmpbutton->m_ButtonSprite.SetPosition (375, 100);
	tmpbutton->SetNextScreenID (CScreen::GAME);
	m_ButtonList.push_back(tmpbutton);

	tmpbutton = new CMenuButton;
	tmpbutton->Init("test_button.png", sf::Vector2i (50,50), CButton::DEACTIVATED);
	tmpbutton->m_ButtonSprite.SetPosition (375, 175);
	tmpbutton->SetNextScreenID (CScreen::INTRO);
	m_ButtonList.push_back(tmpbutton);

	tmpbutton = new CMenuButton;
	tmpbutton->Init("Exit.png", sf::Vector2i (100,50), CButton::ACTIVATED);
	tmpbutton->m_ButtonSprite.SetPosition (375, 250);
	tmpbutton->SetNextScreenID (CScreen::EXIT);
	m_ButtonList.push_back(tmpbutton);
}

// release the different buttons
CMainMenue::~CMainMenue ()
{
	// release the buttons
	vector<CMenuButton *>::iterator itButtons;
	for (itButtons = m_ButtonList.begin (); itButtons != m_ButtonList.end (); itButtons++)
		delete (*itButtons);
	m_ButtonList.clear ();
}

int CMainMenue::Run ()
{
	int MouseX;
	int MouseY;

	int NextScreen = CScreen::EXIT;
	bool Focused = true; // if the Window has the Focus or not
	bool running = true;

	const sf::Input &Input = WINDOW->GetInput ();
	sf::Event Event;

	vector<CMenuButton *>::iterator ButtonIT;

	// Reset every button state
	for (ButtonIT = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
		(*ButtonIT)->ResetState ();

	// fade the menu slowly in
	Fade (0, 255, 1.25);

	while (running)
	{
		// Update the Framework
		g_pFramework->Update();

		// check if we have the Focus
		if (Focused)
		{
			// first lets process the Events
			while (WINDOW->GetEvent (Event) )
			{
				if (Event.Type == sf::Event::Closed)
				{
					Fade (255, 0, 1.25);
					return CScreen::EXIT;
				}
				else if (Event.Type == sf::Event::LostFocus)
					Focused = false;
				else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::F11)
				{
					// Take a Screenshot
					sf::Image Screenshot = WINDOW->Capture ();
					Screenshot.SaveToFile ("Screenshots/screenshot.png");
				}
			}

			// now we can handle the real-time Input
			//Input = WINDOW->GetInput ();
			MouseX = Input.GetMouseX ();
			MouseY = Input.GetMouseY ();

			for (ButtonIT = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
			{
				// now check if the Button is not deactivated or invisible
				if ((*ButtonIT)->GetState () != CButton::INVISIBLE && (*ButtonIT)->GetState () != CButton::DEACTIVATED)
				{
					// now check if the mouse is over one of them
					if ((*ButtonIT)->IsMouseOver (MouseX, MouseY))
					{
						// Set the ButtonState to MOUSEOVER
						(*ButtonIT)->SetState (CButton::MOUSEOVER);

						// now we can check if the Mouse button is down too
						if (Input.IsMouseButtonDown (sf::Mouse::Left) )
						{
							running = false;
							NextScreen = (*ButtonIT)->GetNextScreenID ();
						}
					}
					else
						(*ButtonIT)->ResetState ();
				}
			}

			// because we have nothing to update here we can just render everything
			Render ();
		}
		else
		{
			// check if we gained back our focus
			while (WINDOW->GetEvent (Event) )
			{
				if (Event.Type == sf::Event::GainedFocus)
					Focused = true;
			}
		}

	}

	// before going to the next scene, fade the menu out
	Fade (255, 0, 1.25);

	// So the MainMenue isn't running anymore so go to the NextScreen
	return NextScreen;
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

void CMainMenue::Fade (float from, float to, float duration)
{
	std::cout << "Fading from " << from << " to " << to << " in " << duration <<" seconds." << std::endl;
	bool  fading = true; // if the menu is still fading in or not

	vector<CMenuButton *>::iterator ButtonIT;

	m_BGSprite.AddEffect (new CFadeEffect);
	m_BGSprite.GetLastEffect ()->Start (m_BGSprite, from, to, duration);

	for (ButtonIT  = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
	{
		// now add the effect
		(*ButtonIT)->m_ButtonSprite.AddEffect (new CFadeEffect);
		(*ButtonIT)->m_ButtonSprite.GetLastEffect ()->Start ((*ButtonIT)->m_ButtonSprite, from, to, duration);
	}

	// slowly fade the menu
	while (fading)
	{
		fading = false;

		// Update the Background and the buttons
		m_BGSprite.Update ();

		if (m_BGSprite.IsActive () )
			fading = true;

		for (ButtonIT  = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
		{
				(*ButtonIT)->m_ButtonSprite.Update   ();
				if ( (*ButtonIT)->m_ButtonSprite.IsActive () )
					fading = true;
		}

		g_pFramework->Update ();
		Render ();
	}

	// because I don't trust "fading", stop every effect manually and delete it
	m_BGSprite.GetLastEffect ()->Stop (m_BGSprite, false);
	m_BGSprite.ClearEffects ();

	for (ButtonIT  = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
	{
		(*ButtonIT)->m_ButtonSprite.GetLastEffect ()->Stop ((*ButtonIT)->m_ButtonSprite, false);
		(*ButtonIT)->m_ButtonSprite.ClearEffects ();
	}

	std::cout << "Fading from " << from << " to " << to << " in " << duration <<" seconds. DONE" << std::endl;
}

void CMainMenue::Render ()
{
	WINDOW->Clear ();
	WINDOW->Draw (m_BGSprite);

	vector<CMenuButton *>::iterator ButtonIT;

	for (ButtonIT  = m_ButtonList.begin (); ButtonIT != m_ButtonList.end (); ButtonIT++)
	{
		(*ButtonIT)->Update ();

		WINDOW->Draw ((*ButtonIT)->m_ButtonSprite);
	}

	// and don't forget to display it
	g_pFramework->Render ();
}
