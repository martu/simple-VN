/*
 * CFontmanager.cpp
 *
 *  Created on: 05.08.2010
 *      Author: Martu
 */

#include "Conversation/CFontmanager.hpp"

void CFontManager::Init (const string sDatapath)
{
	// just set the Datapath in which the Fonts are located
	m_sDatapath = sDatapath;
}

// checks if the Font is already loaded (if not it will be loaded) and returns
// an Instance to the Font
const sf::Font &CFontManager::getFont (const string sFilename, int Charsize)
{
	// test if we should just return sfmls default font
	if (sFilename.compare ("DEFAULT") == 0)
		return sf::Font::GetDefaultFont ();

	// create an iterator for our Fontmap
	map<const string, const sf::Font *>::iterator it;

	// now check if the desired Font is already loaded and in our Fontmap
	it = m_FontList.find (sFilename);
	// if it is not at the end of the map the Font is loaded and we can return it
	if ( it != m_FontList.end () )
	{
		return *it->second;
	}

	// combines the Datapath and the Filename to get the full path to load
	string comb;
	comb.append (m_sDatapath);
	comb.append (sFilename);

	// now create a new instance for an Font
	sf::Font *newFont;

	// if we are still here, then the Font must be loaded and pushed into our map
	newFont = new sf::Font;
	newFont->LoadFromFile (comb, Charsize);
	m_FontList[sFilename] = newFont;

	return *newFont;
}

// unloads an Font
void CFontManager::releaseFont (const string sFilename)
{
	//our iterator
	map<const string, const sf::Font *>::iterator it;

	// find the Font
	it = m_FontList.find (sFilename);

	if ( it == m_FontList.end () )
		return; // couldn't find the Font

	delete it->second; // delete the Font
	m_FontList.erase (it);
}

// unloads every Font in the map
void CFontManager::releaseAll ()
{
	//our iterator
	map<const string, const sf::Font *>::iterator it;

	for (it = m_FontList.begin (); it != m_FontList.end (); it++)
		delete it->second;

	m_FontList.clear ();
}
