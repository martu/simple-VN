/*
 * CBackground.hpp
 *
 *  Created on: 04.10.2010
 *      Author: Martu
 */

#ifndef CBACKGROUND_HPP_
#define CBACKGROUND_HPP_

#include "Conversation/CFXSprite.hpp"
#include "Conversation/CImageManager.hpp"

// class for managing the backgrounds of a comversation
class CBackground
{
private:
	sf::RenderWindow *m_pWindow; // window needed for rendering

	map<const string, CFXSprite> m_OldBackground; // the old background
	map<const string, CFXSprite> m_NewBackground; // the new background

	bool m_bIsActive; // if the background is still changing or not
	bool m_bChangeBackground; // if we neew to apply the effects or not

public:
	~CBackground (); // destructor, frees the images currently used

	void Init (sf::RenderWindow *pWindow);

	void SetBackgroundColor  (sf::Color Color);
	void SetBackgroundSprite (const string sFileName);
	void SetTransition       (GFXEffect *pBGIn, GFXEffect *pBGOut);
	void SetEffect           (GFXEffect *pEffect);

	bool IsActive () {return m_bIsActive;};

	void StopEffects (bool bToTarget = false);
	void Update ();
	void Swap   ();
	void Render ();
};

#endif /* CBACKGROUND_HPP_ */
