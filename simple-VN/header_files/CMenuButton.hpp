/*
 * CMenuButton.hpp
 *
 *  Created on: 31.08.2010
 *      Author: Martu
 */

#ifndef CMENUBUTTON_HPP_
#define CMENUBUTTON_HPP_

#include "Conversation/CButton.hpp"

// represents a button for the Main menu
class CMenuButton : public CButton
{
private:
	int m_NextScreen;

public:
	void SetNextScreenID (int NextScreen) {m_NextScreen = NextScreen;};
	int GetNextScreenID () {return m_NextScreen;};
};


#endif /* CMENUBUTTON_HPP_ */
