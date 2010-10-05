/*
 * CFontmanager.hpp
 *
 *  Created on: 05.08.2010
 *      Author: Martu
 */

#ifndef CFONTMANAGER_HPP_
#define CFONTMANAGER_HPP_

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "TSingleton.hpp"

using namespace std;

// only one instance of this class is allowed
#define g_pFontManager CFontManager::GET ()

// Class for Managing Fonts.
class CFontManager : public TSingleton<CFontManager>
{
private:
	string m_sDatapath; // Path to Font Directory
	map<const string, const sf::Font*> m_FontList; // map with pointers of all loaded Fonts

public:
	void Init (const string sDatapath);
	const sf::Font & getFont (const string sFilename, int Charsize = 30);
	void releaseFont (const string sFilename);
	void releaseAll ();
};



#endif /* CFONTMANAGER_HPP_ */
