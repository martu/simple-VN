/*
 * CAnisprite.hpp
 *
 *  Created on: 12.08.2010
 *      Author: Martu
 */

#ifndef CANISPRITE_HPP_
#define CANISPRITE_HPP_

#include "CFXSprite.hpp"
#include "CImageManager.hpp"

// class for animated sprites. The numbering of the frames begins at 0.
class CAniSprite : public CFXSprite
{
private:
	std::string m_sFileName; // Name of our Image

	int m_FrameWidth;  // width of a single frame
	int m_FrameHeight; // height of a single frame
	int m_NumFramesX;  // number of frames in a single row

public:
	CAniSprite  ();
	~CAniSprite ();
	void Init (std::string FileName, int FrameWidth, int FrameHeight);
	void Calculate (float FrameNumber);

	sf::Vector2i GetFrameSize () {return sf::Vector2i (m_FrameWidth, m_FrameHeight);};
};

#endif /* CANISPRITE_HPP_ */
