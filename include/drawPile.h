/**
* @author Blake McLachlin
* @date November 4, 2018
*/

#ifndef DRAWPILE_H
#define DRAWPILE_H

#include "cardCollection.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

/**
* @class drawPile, the draw pile for a card game.
* Players draw from the pile when drawing cards
* during a game
*/
class drawPile : public cardCollection {
public:
	drawPile(const int& game);

	virtual ~drawPile() {}

	/**
	* Displays the drawPile, this function has an empty body
	* because a player should not be allowed to see the drawPile
	*/
	void show();

	/**
	* Deals 7 cards from the draw pile to each players hand
	* @param H the players hand
	* @param C the CPU's hand
	*/
	void deal(cardCollection *H, cardCollection *C);

protected:
};

#endif // DRAWPILE_H
