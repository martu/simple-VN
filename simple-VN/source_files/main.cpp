/*
 * main.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martu
 */

#include "CFramework.hpp"

#include "Screens.hpp"

int main ()
{
	// Initialize the different managers
	g_pImageManager->Init ("Data/Images/");
	g_pFontManager->Init  ("Data/Font/");

	// Initialize the Framework
	g_pFramework->Init (800, 600, 32, false, true, "testVN", true);

	// Initialize the Screens
	int CurScreen  = CScreen::INTRO;
	int NewScreen  = CScreen::INTRO; // Begin with the Intro
	int LastScreen = CScreen::INTRO;

	map<int, CScreen *> Screens;

	CIntro Intro;
	Screens[CScreen::INTRO] = &Intro;

	CMainMenue MainMenue;
	Screens[CScreen::MAINMENUE] = &MainMenue;

	CGame Game;
	Screens[CScreen::GAME] = &Game;

	// Set the images for the Intro
	Intro.SetSprite ("Intro/Intro.png");
	Intro.SetSprite ("Backgrounds/Standard.png");

	// Main Game loop
	while (NewScreen > CScreen::EXIT)
	{
		if (NewScreen == CScreen::LASTONE)
			CurScreen = LastScreen;
		else
		{
			LastScreen = CurScreen;
			CurScreen = NewScreen;
		}

		NewScreen = Screens[CurScreen]->Run ();
	}

	// release all the stuff of the managers and destroy them
	g_pImageManager->releaseAll ();
	g_pImageManager->DEL ();
	g_pFontManager->releaseAll  ();
	g_pFontManager->DEL  ();

	// Framework is not longer running, so we can exit
	g_pFramework->Quit ();
	g_pFramework->DEL ();

	return 0;
}
