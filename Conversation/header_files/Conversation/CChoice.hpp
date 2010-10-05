/*
 * CChoice.hpp
 *
 *  Created on: 30.08.2010
 *      Author: Martu
 */

#ifndef CCHOICE_HPP_
#define CCHOICE_HPP_

#include "CButton.hpp"
#include "CFontManager.hpp"

// defines a choice Button
class CChoice : public CButton
{
private:
	string m_sFlag;
	sf::String m_sName; // Text displayed on the Button

	void ComputeNamePos ();

public:
	void Render (sf::RenderWindow *pWindow);

	void SetFont   (string sFont);
	void SetChoice (string sName, string sFlag);
	void SetMouseOver (bool MouseOver);

	string GetFlag () {return m_sFlag;};
};

#endif /* CCHOICE_HPP_ */
