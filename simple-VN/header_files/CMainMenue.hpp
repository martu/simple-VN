/*
 * CMainmenue.hpp
 *
 *  Created on: 04.08.2010
 *      Author: Martu
 */

#ifndef CMAINMENUE_HPP_
#define CMAINMENUE_HPP_

#include "CScreen.hpp"
#include "Screens.hpp"
#include "CMenuButton.hpp"

namespace mainmenue
{
	enum SUBSCREENID
	{
		MAIN,
		STARTGAME,
		EXIT,
	};
}

// Screen for displaying and handling the mainmenue
class CMainMenue : public CScreen
{
private:
	CFXSprite m_BGSprite;  // Sprite for the background

	vector<CMenuButton *> m_ButtonList; // List of the available buttons

	void Fade (float from, float to, float duration);
	void Render  ();

public:
	CMainMenue ();
	~CMainMenue ();
	int Run ();
};

#endif /* CMAINMENUE_HPP_ */
