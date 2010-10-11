/*
 * CFramework.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martu
 */

#include "CFramework.hpp"

// Initialize all the important things like the window, timer and so on
bool CFramework::Init (int ScreenWidth, int ScreenHeight,
			int ColorDepth, bool bFullscreen, bool bVSync, const string &Title, bool bShowFPS)
{
	if (bFullscreen)
	{
		m_pWindow = new sf::RenderWindow (sf::VideoMode (ScreenWidth, ScreenHeight, ColorDepth), Title, sf::Style::Fullscreen);
	}
	else
	{
		m_pWindow = new sf::RenderWindow (sf::VideoMode (ScreenWidth, ScreenHeight, ColorDepth), Title);
	}

	m_pWindow->UseVerticalSync (bVSync);

	m_pWindow->Clear ();

	m_bShowFPS = bShowFPS;

	if (m_bShowFPS)
	{
		m_FPS.SetFont     (sf::Font::GetDefaultFont () );
		m_FPS.SetSize     (15);
		m_FPS.SetColor    (sf::Color::Black);
		m_FPS.SetPosition (sf::Vector2f (20, 20) );
	}

	// Initialize the Timer
	m_fCurTime  = 0.0f;
	m_fElapsed  = 0.0f;

	return true;
}

// Make sure all is deleted and closed correctly
void CFramework::Quit ()
{
	m_pWindow->Close ();

	if (m_pWindow != NULL)
	{
		delete (m_pWindow);
		m_pWindow = NULL;
	}
}

// just update the timer
void CFramework::Update ()
{
	// Update the Timer
	m_fCurTime = Timer.GetElapsedTime ();
	m_fElapsed = m_pWindow->GetFrameTime ();

	// if we should display the fps, calculate it
	if (m_bShowFPS)
	{
		sprintf (m_sConvFPS, "FPS: %.2f", 1.f / m_pWindow->GetFrameTime () );
		m_FPS.SetText (m_sConvFPS);
	}
}

// Renders the current Screen
void CFramework::Render ()
{
	// if we should display the fps render it too
	if (m_bShowFPS)
		m_pWindow->Draw (m_FPS);

	// just display what was being rendered
	m_pWindow->Display ();
}
