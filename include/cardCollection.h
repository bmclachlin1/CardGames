/**
* @author Blake McLachlin
* @date October 31, 2018
*/

#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include "card.h"
#include <vector>

/**
* @class cardCollection defines a collection of cards and
* the functions associated with them
*/
class cardCollection {
	friend class Card;
public:
	cardCollection();
	virtual ~cardCollection();

	/**
	* moves a card from the cardCollection object calling the function
	* (*this) to another cardCollection
	* @param c a cardCollection
	*/
	void moveCard(cardCollection* receiver, Card* c);

	/**
	* Inserts a Card into a Card Collection
	* @param c the card to be added
	*/
	void insertCard(Card* c);

	/**
	* Checks if the cardCollection is empty
	* @return true if the cardCollection is empty, false otherwise
	*/
	bool isEmpty();

	/**
	* Displays the cardCollection, depending on the rules on what CAN be
	* displayed
	*/
	virtual void show() = 0;

	/**
	* Function to return the card pointer in the vector at position i
	*/
	Card* getAt(int i);

	/**
	* Function to return the card pointed at in the vector at position i
	* @param i the index in the vector
	* @return Card* a pointer to a card
	*/
	Card getAtCard(int i);

	/**
	* Function to return the card in a card collection who's
	* Rank matches the parameter passed in
	* @param c the card who's Rank in the card collection we are looking for
	* @return Card* a pointer to a card
	*/
	Card* getRankAt(Card* c);

	/**
	* Function to return true if the card collection contains the same
	* rank as the card being passed in
	* @param c the card who's Rank in the card collection we are looking for
	* @return true if there exists a card that matches
	*/
	bool containsRank(Card* c);

	/**
	* Overloaded output stream operator
	* @param os a reference to an ostream. c, a reference to a cardCollection
	* @return ostream& the output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, cardCollection& c);

	/**
	* gets the size of the vector deck
	* @return The size of the vector deck
	*/
	int getSize() const;

	/**
	* This function is implemented in drawPile.h
	*/
	virtual void deal(cardCollection *H, cardCollection *C) {}

protected:
	/**< The size of the cardCollection*/
	int sizeOf;
	/**< A vector of pointers that represents the cardCollection*/
	std::vector<Card*> deck;
};

#endif
