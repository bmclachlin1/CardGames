/**
* @author Cassady Campos
* @date November 6, 2018
*/

#ifndef PLAYERHAND_H
#define PLAYERHAND_H
#include "cardCollection.h"

#include "cardCollection.h"

/**
* @class playerHand defines a collection of cards and
*  functions associated with them
*/
class playerHand : public cardCollection {
public:
	playerHand();
	virtual ~playerHand() {}

	/**
  * Displays the users hand
	*/
	void show();

protected:
};
#endif // CARDCOLLECTION_H
