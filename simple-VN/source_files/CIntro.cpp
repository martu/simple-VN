/*
 * CIntro.cpp
 *
 *  Created on: 22.07.2010
 *      Author: Martu
 */

#include "CIntro.hpp"


// for description of the Functions see 'CScreen.hpp'

CIntro::CIntro ()
{
	// Nothing to do here
}

// sets the sprites for the Intro
void CIntro::SetSprite (string path)
{
	m_SpritePaths.push_back (path);
}

int CIntro::Run ()
{
	vector<CFXSprite *> Sprites;

	// first load the sprites
	vector<CFXSprite *>::iterator itSprite;
	vector<string>::iterator itPaths;
	CFXSprite *tmpSprite;
	for (itPaths = m_SpritePaths.begin (); itPaths != m_SpritePaths.end (); itPaths++)
	{
		tmpSprite = new CFXSprite;
		tmpSprite->SetImage ( g_pImageManager->getImage ( (*itPaths) ) );
		Sprites.push_back (tmpSprite);
	}

	float fCurDur = 0.0f;

	bool FadeIn  = true;
	bool FadeOut = false;
	bool running = true;

	sf::Event Event;

	int   CurrentSprite   = 0; // begin at the first sprite
	float fFadeDuration   = 0.75;
	float fSpriteDuration = 1.25;

	m_bEffectSet = false;

	while (running)
	{
		tmpSprite = Sprites.at (CurrentSprite);

		// Update the Framework
		g_pFramework->Update();

		// process the Events
		while (WINDOW->GetEvent (Event) )
		{
			if (Event.Type == sf::Event::Closed)
				return CScreen::EXIT;

			// When F11 is pressed, take a Screenshot
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::F11)
			{
				sf::Image Screenshot = WINDOW->Capture ();
				Screenshot.SaveToFile ("Screenshots/screenshot.png");
			}

			// If Esc is pressed exit the Intro
			else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)
				running = false;
		}

		// when where at the last sprite, exit the Intro
		if (FadeIn)
		{
			FadeIn = Fade (tmpSprite, 0, 255, fFadeDuration);
		}
		else if (FadeIn == false && FadeOut == false && fCurDur < fSpriteDuration)
		{
			fCurDur += g_pFramework->GetElapsed ();

			// test if the new time is greater or equal to the spriteDuration
			if (fCurDur >= fSpriteDuration)
				FadeOut = true; // set the FadeOut for this sprite to true
		}
		else if (FadeOut)
		{
			FadeOut = Fade (tmpSprite, 255, 0, fFadeDuration);

			// test if the fading is over
			if (FadeOut == false)
			{
				CurrentSprite++; // go to the next sprite
				fCurDur = 0;       // reset the timer
				FadeIn  = true;    // and fade in the next sprite
			}
		}

		// test if this was the last sprite
		if (CurrentSprite >= static_cast<int> (Sprites.size () ) )
			running = false;

		// Render the stuff
		WINDOW->Clear ();
		WINDOW->Draw (*tmpSprite);
		g_pFramework->Render ();
	}

	// don't forget to release the images and delete the sprites
	for (itPaths = m_SpritePaths.begin (); itPaths != m_SpritePaths.end (); itPaths++)
		g_pImageManager->releaseImage ( (*itPaths) );

	for (itSprite = Sprites.begin (); itSprite != Sprites.end (); itSprite++)
		delete ((*itSprite));

	Sprites.clear ();

	// and now go the MainMenue
	return CScreen::MAINMENUE;
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// returns true if it is still fading
bool CIntro::Fade (CFXSprite *tmp, float from, float to, float duration)
{
	bool StillFading = true;

	// first test if the effect is already set
	if (m_bEffectSet == false)
	{
		tmp->AddEffect     (new CFadeEffect);
		tmp->GetLastEffect ()->Start (*tmp, from, to, duration);

		m_bEffectSet = true;
	}

	// when the effect is set, update the given Sprite
	if (m_bEffectSet)
	{
		tmp->Update ();

		StillFading = true;

		// test if the effect is still active
		if (tmp->IsActive () == false)
		{
			// it isn't active anymore, so stop and delete the effect
			tmp->GetLastEffect ()->Stop (*tmp, false);
			tmp->ClearEffects ();

			// also set "m_bEffectSet" to false
			m_bEffectSet = false;

			StillFading = false;
		}
	}

	return StillFading;
}
