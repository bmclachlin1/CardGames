/**
* @author Blake McLachlin
* @date November 6, 2018
*/

#ifndef DISCARD_H
#define DISCARD_H
#include "cardCollection.h"

/**
* @class discardPile defines a collection of cards that
* acts as the discard pile in a card game.
*/
class discardPile : public cardCollection {
public:
	discardPile();
	virtual ~discardPile() {}

	/**
	* This function shows the last card played
	*/
	void show();
protected:
};

#endif
