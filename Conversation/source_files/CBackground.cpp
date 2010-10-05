/*
 * CBackground.cpp
 *
 *  Created on: 04.10.2010
 *      Author: Martu
 */

#include "Conversation/CBackground.hpp"

// the destructor it frees the images associated with the current sprites
CBackground::~CBackground ()
{
	map<const string, CFXSprite>::iterator it;
	for (it = m_OldBackground.begin (); it != m_OldBackground.end (); it++)
		g_pImageManager->releaseImage ((*it).first);

	for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
		g_pImageManager->releaseImage ((*it).first);
}

// just sets the renderwindow and clears the maps
void CBackground::Init (sf::RenderWindow *pWindow)
{
	m_pWindow = pWindow;

	m_OldBackground.clear ();
	m_NewBackground.clear ();
}

// tests if the color is already in the map, otherwise set it
void CBackground::SetBackgroundColor  (sf::Color Color)
{
	CFXSprite tmp; // create the color and set the size
	tmp.SetColor (Color);
	tmp.Resize   (m_pWindow->GetWidth (), m_pWindow->GetHeight () );

	// search if we already have a color
	map<const string, CFXSprite>::iterator it = m_OldBackground.find ("Color");

	if (it != m_OldBackground.end () )
	{
		// ok we have found the color, now check if it's the same as the new one
		if ((*it).second.GetColor () != Color)
		{
			// no it isn't, so set the new color
			m_NewBackground["Color"] = tmp;
			m_bChangeBackground = true;
		}
		else
			m_NewBackground["Color"] = (*it).second; // it's the same color, so just add it to the new background
	}
	else
	{
		// no color exists, so create one
		m_NewBackground["Color"] = tmp;
		m_bChangeBackground = true;
	}
}

// tests if the sprite is already in the map, if not create it and store it
void CBackground::SetBackgroundSprite (const string sFileName)
{
	// first test if the Filename is empty
	if (sFileName.empty () == false)
	{
		// it is not empty so test if it is NONE
		if (sFileName.compare ("NONE") == 0)
		{
			// ok we shouldn't display a new Background and just fade the old one out
			m_bChangeBackground = true;
		}
		else
		{
			// ok we should display a new Background. So first
			// search if we already have the required sprite
			map<const string, CFXSprite>::iterator it = m_OldBackground.find (sFileName);

			if (it != m_OldBackground.end () )
			{
				// we have the sprite, so copy it to the new background
				m_NewBackground[sFileName] = (*it).second;
			}
			else
			{
				// ok we need to get a new instance of the image
				CFXSprite tmp;
				tmp.SetImage (g_pImageManager->getImage (sFileName) );

				// now set some basic variables
				tmp.SetCenter   (sf::Vector2f (tmp.GetSize ().x / 2, tmp.GetSize ().y / 2) );
				tmp.SetPosition (tmp.GetSize ().x / 2, tmp.GetSize ().y / 2);
				tmp.SetScale    (sf::Vector2f (1,1) );
				tmp.SetSubRect  (sf::IntRect (0,0, tmp.GetSize ().x, tmp.GetSize ().y));

				// and now copy the new sprite to the Background
				m_NewBackground[sFileName] = tmp;
				m_bChangeBackground = true;
			}
		}
	}
}

// Sets the transitions if needed
void CBackground::SetTransition (GFXEffect *pBGIn, GFXEffect *pBGOut)
{
	if (m_bChangeBackground)
	{
		map<const string, CFXSprite>::iterator it;

		// first the old background
		for (it = m_OldBackground.begin (); it != m_OldBackground.end (); it++)
			GFX::SetEffect ((*it).second, *pBGOut);

		// now the new background
		// but first set the needed delay
		pBGIn->m_fDelay = pBGOut->m_fDuration;

		for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
			GFX::SetEffect ((*it).second, *pBGIn);

		m_bIsActive = true;
		m_bChangeBackground = false;
	}
}

// sets a effect to the new backgrounds
void CBackground::SetEffect (GFXEffect *pEffect)
{
	map<const string, CFXSprite>::iterator it;

	// now the new background
	for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
		GFX::SetEffect ((*it).second, *pEffect ); // kinda ugly but as long as it works...
}

// stops every effect on the backgrounds, if ToTarget = true the effects will
// be set to the target value, otherwise just canceled
void CBackground::StopEffects (bool bToTarget)
{
	GFXEffect tmp;
	tmp.m_Type = GFXEffect::STOPALL;
	tmp.m_bSetToTarget = bToTarget;

	map<const string, CFXSprite>::iterator it;

	for (it = m_OldBackground.begin (); it != m_OldBackground.end (); it++)
		GFX::SetEffect ((*it).second, tmp);

	// now the new background
	for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
		GFX::SetEffect ((*it).second, tmp);
}

// Updates the Background
void CBackground::Update ()
{
	bool bIsOldActive = false;
	bool bIsNewActive = false;

	map<const string, CFXSprite>::iterator it;
	for (it = m_OldBackground.begin (); it != m_OldBackground.end (); it++)
	{
		(*it).second.Update ();

		if ((*it).second.IsActive () == true)
			bIsOldActive = true;
	}

	for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
	{
		(*it).second.Update ();

		if ((*it).second.IsActive () == true)
			bIsNewActive = true;
	}

	if (bIsOldActive == false && bIsNewActive == false)
		m_bIsActive = false;
}

// clears the old background and copy the new background to the old one and clear it then too
void CBackground::Swap ()
{
	// first we need to stop the effects, because otherwise we end up with a few invalid pointers
	StopEffects (true);

	m_OldBackground.clear ();
	m_OldBackground = m_NewBackground;
	m_NewBackground.clear ();
}

// Renders the Background
void CBackground::Render ()
{
	map<const string, CFXSprite>::iterator it;

	for (it = m_OldBackground.begin (); it != m_OldBackground.end (); it++)
		m_pWindow->Draw ((*it).second);

	// now the new background
	for (it = m_NewBackground.begin (); it != m_NewBackground.end (); it++)
		m_pWindow->Draw ((*it).second);
}
