/*
 * CScreen.hpp
 *
 *  Created on: 21.07.2010
 *      Author: Martu
 */

#ifndef CSCREEN_HPP_
#define CSCREEN_HPP_

#include "CFramework.hpp"

#define WINDOW g_pFramework->GetWindow ()

/*
 * class for managing different screens for a game (game, menu, intro, ...)
 * all the screens just have to inherit this class and implement
 * ALL of the functions. If the 'Run' function returns >= 0 the
 * program changes the screen. If it returns -1 the program will exit.
 */
class CScreen
{
public:
	virtual ~CScreen () {};

	virtual int Run () = 0;

	// defines the Numbers of the screens
	enum SCREENID
	{
		 EXIT = -1,
		 INTRO,
		 MAINMENUE,
		 GAME,
		 LASTONE,
	};
};

#endif /* CSCREEN_HPP_ */
