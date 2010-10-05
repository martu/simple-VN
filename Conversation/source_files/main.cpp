/*
 * main.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martu
 */

#include "CConversation.hpp"
#include <iostream>

// creates a few sample scenes
void CreateSampleScenes (CConversation *pConversation)
{
	// just create two small scenes for the beginning
	SScene scene1;
	scene1.m_ID = 1;
	scene1.m_bIsRead = false;
	scene1.m_BGColor = sf::Color::Red;
	scene1.m_sSpeaker.append ("Martu");
	scene1.m_sText.append ("This should be the first scene ;P");
	scene1.m_fDuration = -1;
	pConversation->AddScene (scene1);

	SScene scene2;
	scene2.m_ID = 2;
	scene2.m_bIsRead = false;
	scene2.m_BGColor = sf::Color::Blue;
	scene2.m_sSpeaker.append ("Martu");
	scene2.m_sText.append ("This should be the second scene.\nThe Background color should have changed...");
	scene2.m_fDuration = -1;
	pConversation->AddScene (scene2);
}

int main ()
{
	// Initialize the different managers
	g_pImageManager->Init ("./");
	g_pFontManager->Init  ("./");

	// create the renderWindow
	sf::RenderWindow app;
	app.Create (sf::VideoMode (800, 600, 32), "Conversation sample");

	// create out sample conversation
	CConversation m_SampleConv;

	// initialize the conversation with default objects
	m_SampleConv.Init (&app);

	// now retrieve the default objects so we can delete them later
	CTextArea *m_pTextArea = m_SampleConv.GetTextArea ();
	map<int, SCharacter *> *m_pCharacters = m_SampleConv.GetCharacters ();
	vector<string> *m_pFlags = m_SampleConv.GetFlags ();

	// creates a few sample scenes
	CreateSampleScenes (&m_SampleConv);

	// don't forget to go to the first scene
	m_SampleConv.GoToScene (0);

	// main loop
	while (app.IsOpened () )
	{
		sf::Event Event;

		// Get the Coordinates of the mouse, and also convert them to the current view
		sf::Vector2f Mouse = app.ConvertCoords(app.GetInput ().GetMouseX (), app.GetInput ().GetMouseY () );

		// get the pointer to the choices of the current scene
		vector<CChoice *> *pChoices = m_SampleConv.GetChoices ();

		// processing the events
		while (app.GetEvent (Event) )
		{
			if (Event.Type == sf::Event::Closed)
				app.Close ();

			// If right is pressed go to the next scene
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Right)
			{
				// but only go to the next scene, when there aren't any choices
				if (pChoices->empty () )
				{
					// test if we're displaying everything
					if (m_SampleConv.IsActive () )
					{
						// it is still active so before changing the scene display everything
						m_SampleConv.DisplayAll ();
					}
					else
						m_SampleConv.NextScene ();
				}
			}

			// if left is pressed go to the previous scene
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Left)
			{
				// test if we're displaying everything
				if (m_SampleConv.IsActive () )
				{
					// it is still active so before changing the scene display everything
					m_SampleConv.DisplayAll ();
				}
				else
					m_SampleConv.PrevScene ();
			}

			// if space is pressed, hide or show the TextArea
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Space)
			{
				// check if it is already hidden
				if (m_SampleConv.IsHidden () )
				{
					// it is already hidden, so show it
					m_SampleConv.SetHidden (false);
				}
				else
				{
					// it's not hidden, so hide it
					m_SampleConv.SetHidden (true);
				}
			}
		}

		// now see if there are any choices and if there are process them
		if (pChoices->empty () == false)
		{
			// there are some choices so process them
			vector<CChoice *>::iterator itCH;

			// go trough every choice
			for (itCH = pChoices->begin (); itCH != pChoices->end (); itCH++)
			{
				// test if the Mouse is over this choice
				if ((*itCH)->IsMouseOver (Mouse.x, Mouse.y) )
				{
					// ok the mouse is over this choice, so set it's state to MouseOver
					(*itCH)->SetMouseOver (true);

					// now we know that the mouse is over this button, check if
					// the left mousebutton is pressed too
					if (app.GetInput ().IsMouseButtonDown (sf::Mouse::Left) )
					{
						// ok the left mousebutton is down so set the Flag form this key
						// and change to the next scene
						m_SampleConv.SetFlag ((*itCH)->GetFlag () );
						m_SampleConv.NextScene ();
					}
				}
				else
					(*itCH)->SetMouseOver (false); // if the mouse is not over the button
			}
		}

		// Update the conversation
		m_SampleConv.Update ();

		// clear the whole screen
		app.Clear ();

		// render the complete conversation
		m_SampleConv.Render ();

		// and display the screen
		app.Display ();
	}

	// release the TextArea, Characters and the flags
	delete (m_pTextArea);

	m_pFlags->clear ();
	delete (m_pFlags);

	map<int, SCharacter *>::iterator itC;

	for (itC = m_pCharacters->begin (); itC != m_pCharacters->end (); itC++)
		delete (itC->second);

	m_pCharacters->clear ();
	delete (m_pCharacters);


	// release all the stuff of the managers and destroy them
	g_pImageManager->releaseAll ();
	g_pImageManager->DEL ();
	g_pFontManager->releaseAll  ();
	g_pFontManager->DEL  ();

	return 0;
}
