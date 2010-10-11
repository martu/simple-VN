/*
 * CFramework.hpp
 *
 *  Created on: 20.07.2010
 *      Author: Martu
 */

#ifndef CFRAMEWORK_HPP_
#define CFRAMEWORK_HPP_

#include <stdio.h>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Conversation/CImageManager.hpp"
#include "Conversation/CFontManager.hpp"
#include "Conversation/TSingleton.hpp"

using namespace std;

#define g_pFramework CFramework::GET ()

class CFramework : public TSingleton<CFramework>
{
private:
	sf::RenderWindow *m_pWindow; // our Renderwindow
	sf::Clock Timer;

	float m_fCurTime;  // current Time ( how long the programm is running)
	float m_fElapsed;  // seconds since last frame

	// FPS //
	bool m_bShowFPS; // if the frames per second should be shown or not
	char       m_sConvFPS [13]; // used for storing the fps-string
	sf::String m_FPS;  // string for showing the fps

public:
	bool Init (int ScreenWidth, int ScreenHeight,
				int ColorDepth, bool bFullscreen, bool bVSync, const string &Title, bool bShowFPS = false);
	void Quit ();
	void Update ();
	void Render ();

	sf::RenderWindow *GetWindow  () {return m_pWindow;};
	float             GetCurTime () {return m_fCurTime;};
	float             GetElapsed () {return m_fElapsed;};
};

#endif /* CFRAMEWORK_HPP_ */
