/**
* @author Cassady Campos
* @date October 31 2018
*/

#include "card.h"

/**
* Setter for Card Rank
* @param r is the Rank to set
*/
void Card::setRank(const Rank& r) {
	cardRank = r;
}

/**
* Getter to get the Card's Rank
*/
Card::Rank Card::getRank() {
	return cardRank;
}

/**
* Setter for Card Face
* @param f is the Face to set
*/
void Card::setFace(const Face& f) {
	cardFace = f;
}

/**
* Getter to get the Card's Face
*/
Card::Face Card::getFace() {
	return cardFace;
}

/**
* Displays card
* @return an output stream containing a representation of the card
*  a "Face:Rank format"
*/
std::ostream& operator<<(std::ostream& os, Card& c) {
	os << c.Face_str[c.cardFace] << ":" << c.Rank_str[c.cardRank];
	return os;
}

/**
* Print a card enum values for save file
*/
std::ostream& Card::printCard(std::ostream& os) {
	os << getFace() << ":" << getRank() << std::endl;

	return os;
}
/**
* Overloaded equals operator
* @return whether the Card's are equal
*/
bool Card::operator==(const Card& c) {
	if (cardRank == c.cardRank && cardFace == c.cardFace)
		return true;

	return false;
}

/**
* Overloaded assignment operator
*/
Card& Card::operator=(const Card& c) {
	cardFace = c.cardFace;
	cardRank = c.cardRank;

	return *this;
}

