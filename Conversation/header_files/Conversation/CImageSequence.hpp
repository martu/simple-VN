/*
 * CImageSequences.hpp
 *
 *  Created on: 09.09.2010
 *      Author: Martu
 */

#ifndef CIMAGESEQUENCES_HPP_
#define CIMAGESEQUENCES_HPP_

#include <map>
#include "CFXSprite.hpp"
#include "CImageManager.hpp"

// defines a sequence of different images
class CImageSequence
{
private:
	map<string, CFXSprite> m_Images; // saves the different images
	vector<string> m_Paths; // saves the paths to these images, used for releasing them
	bool           m_bNeedsUpdate;  // if the sprites needs to be updated or not

	sf::Vector2f    m_Position;
	sf::Vector2f    m_Scale;
	sf::Vector2f    m_Center;
	float           m_fRotation;
	sf::Color       m_Color;
	sf::Blend::Mode m_BlendMode;

	void Update ();

public:
	CImageSequence ();

	void AddImage (string ID, string FileName);

	void SetPosition  (sf::Vector2f Position);
	void SetScale     (sf::Vector2f Scale);
	void SetCenter    (sf::Vector2f Center);
	void SetRotation  (float fRotation);
	void SetColor     (sf::Color Color);
	void SetBlendMode (sf::Blend::Mode BlendMode);

	CFXSprite       *GetImage     (string ID);
	sf::Vector2f    &GetPosition  () {return m_Position;};
	sf::Vector2f    &GetScale     () {return m_Scale;};
	sf::Vector2f    &GetCenter    () {return m_Center;};
	float            GetRotation  () {return m_fRotation;};
	sf::Color       &GetColor     () {return m_Color;};
	sf::Blend::Mode  GetBlendMode () {return m_BlendMode;};
};

#endif /* CIMAGESEQUENCES_HPP_ */
