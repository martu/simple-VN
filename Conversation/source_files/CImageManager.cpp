/*
 * CImagemanager.cpp
 *
 *  Created on: 04.08.2010
 *      Author: Martu
 */

#include "Conversation/CImageManager.hpp"

void CImageManager::Init (const string sDatapath)
{
	// just set the Datapath in which the Images are located
	m_sDatapath = sDatapath;
}

// checks if the Image is already loaded (if not it will be loaded) and returns
// an Instance to the Image
sf::Image & CImageManager::getImage (const string sFilename, bool bSmooth)
{
	// create an iterator for our Imagemap
	map<const string, manager::Image *>::iterator it;

	// combines the Datapath and the Filename to get the full path to load
	string comb;
	comb.append (m_sDatapath);
	comb.append (sFilename);

	// now check if the desired Image is already loaded and in our Imagemap
	it = m_ImageList.find (sFilename);
	// if it is not at the end of the map the Image is loaded and we can return it
	if ( it != m_ImageList.end () )
	{
		// raise the reference counter
		it->second->revCount++;
		return it->second->Image;
	}

	// if we are still here, then the Image must be loaded and pushed into our map
	manager::Image *newImage;
	newImage = new manager::Image;
	newImage->Image.LoadFromFile (comb);
	newImage->Image.SetSmooth (bSmooth);
	newImage->revCount = 1; // first reference
	m_ImageList[sFilename] = newImage;

	return newImage->Image;
}

// unloads an Image
void CImageManager::releaseImage (const string sFilename)
{
	//our iterator
	map<const string, manager::Image *>::iterator it;

	// find the Image
	it = m_ImageList.find (sFilename);

	if ( it == m_ImageList.end () )
		return; // couldn't find the Image

	// check if the revCounter is at zero
	if (it->second->revCount <= 0)
	{
		// We can delete the Image and the struct
		delete it->second;
		m_ImageList.erase (it);
	}
	else
	{
		// there are still some reference of this Image so just lower the revCounter
		it->second->revCount--;
	}
}

// unloads every Image in the map
void CImageManager::releaseAll ()
{
	//our iterator
	map<const string, manager::Image *>::iterator it;

	for (it = m_ImageList.begin (); it != m_ImageList.end (); it++)
	{
		delete it->second;
	}

	m_ImageList.clear ();
}

