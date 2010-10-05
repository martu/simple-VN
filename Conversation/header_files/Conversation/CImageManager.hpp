/*
 * CImagemanager.hpp
 *
 *  Created on: 04.08.2010
 *      Author: Martu
 */

#ifndef CIMAGEMANAGER_HPP_
#define CIMAGEMANAGER_HPP_

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "TSingleton.hpp"

using namespace std;

// only one instance of this class is allowed
#define g_pImageManager CImageManager::GET ()

namespace manager
{
	struct Image
	{
		sf::Image Image;
		int revCount; // How many references this Image has. If this count goes to 0 it can be deleted
	};
}

// Class for Managing Images.
class CImageManager : public TSingleton<CImageManager>
{
private:
	string m_sDatapath; // Path to Image Directory
	map<const string, manager::Image *> m_ImageList; // map with pointers of all loaded Images

public:
	void Init (const string sDatapath);
	sf::Image & getImage (const string sFilename, bool bSmooth = false);
	void releaseImage (const string sFilename);
	void releaseAll ();
};


#endif /* CIMAGEMANAGER_HPP_ */
