/*
 * CImageSequences.cpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#include "Conversation/CImageSequence.hpp"

// constructor
CImageSequence::CImageSequence ()
{
	 m_Position.x = 0;
	 m_Position.y = 0;
	 m_Scale.x    = 1;
	 m_Scale.y    = 1;
	 m_Center.x   = 0;
	 m_Center.y   = 0;

	 m_fRotation  = 0;

	 m_Color.r    = 255;
	 m_Color.g    = 255;
	 m_Color.b    = 255;
	 m_Color.a    = 255;

	 m_BlendMode = sf::Blend::Alpha;
}

// Adds one image to the sequence
void CImageSequence::AddImage (string ID, string FileName)
{
	CFXSprite tmp;
	tmp.SetImage (g_pImageManager->getImage (FileName) );

	m_Paths.push_back (FileName);
	m_Images[ID] = tmp;

	m_bNeedsUpdate = true;
}

// return the sprite with the ID, so it can be passed to the renderwindow.Draw function
// also updates the sprites if necessary
CFXSprite *CImageSequence::GetImage (string ID)
{
	// test if we need to update the sprites
	if (m_bNeedsUpdate)
		Update ();

	 return &m_Images[ID];
}

// Sets a new position
void CImageSequence::SetPosition  (sf::Vector2f Position)
{
	m_Position = Position;
	m_bNeedsUpdate = true;
}

// Sets a new scale
void CImageSequence::SetScale     (sf::Vector2f Scale)
{
	m_Scale = Scale;
	m_bNeedsUpdate = true;
}

// Sets the new Center
void CImageSequence::SetCenter    (sf::Vector2f Center)
{
	m_Center = Center;
	m_bNeedsUpdate = true;
}

// Sets the rotation
void CImageSequence::SetRotation  (float fRotation)
{
	m_fRotation = fRotation;
	m_bNeedsUpdate = true;
}

// Sets a new Color
void CImageSequence::SetColor     (sf::Color Color)
{
	m_Color = Color;
	m_bNeedsUpdate = true;
}

// Sets a new BlendMode
void CImageSequence::SetBlendMode (sf::Blend::Mode BlendMode)
{
	m_BlendMode = BlendMode;
	m_bNeedsUpdate = true;
}

/////////////////////////////////////////
//         PRIVATE FUNCTIONS           //
/////////////////////////////////////////

// Updates the sprites
void CImageSequence::Update ()
{
	map<string, CFXSprite>::iterator it;

	for (it = m_Images.begin (); it != m_Images.end (); it++)
	{
		it->second.SetPosition  (m_Position);
		it->second.SetScale     (m_Scale);
		it->second.SetCenter    (m_Center);
		it->second.SetRotation  (m_fRotation);
		it->second.SetColor     (m_Color);
		it->second.SetBlendMode (m_BlendMode);
	}
}

