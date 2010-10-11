/*
 * CAnisprite.cpp
 *
 *  Created on: 12.08.2010
 *      Author: Martu
 */

#include "Conversation/CAniSprite.hpp"

// constructor
CAniSprite::CAniSprite ()
{
	m_sFileName.clear ();

	m_FrameHeight = 0;
	m_FrameWidth  = 0;
	m_NumFramesX  = 0;
}

// normal destructor, deletes the image used by the sprite
CAniSprite::~CAniSprite ()
{
	g_pImageManager->releaseImage (m_sFileName);
}

// initializes the animation
void CAniSprite::Init (std::string FileName, int FrameWidth, int FrameHeight)
{
	// if there's an old image applied, release it first
	if (!m_sFileName.empty () )
		g_pImageManager->releaseImage (m_sFileName);

	m_sFileName = FileName;

	this->SetImage (g_pImageManager->getImage (m_sFileName) );
	m_FrameWidth  = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_NumFramesX  = static_cast<int> (this->GetSize ().x) / m_FrameWidth;
}

// Renders one Frame of this animation
void CAniSprite::Calculate (float FrameNumber)
{
	// calculate the position of the subrect
	int column = static_cast<int> (FrameNumber) % m_NumFramesX;
	int row    = static_cast<int> (FrameNumber) / m_NumFramesX;

	sf::IntRect subrect (column * m_FrameWidth,
							row * m_FrameHeight,
							column * m_FrameWidth + m_FrameWidth,
							row * m_FrameHeight + m_FrameHeight);

	this->SetSubRect (subrect);
}
