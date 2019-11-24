/**
* @author Cassady Campos
* @date October 31 2018
*/

#ifndef CARD_H
#define CARD_H
#include <iostream>

/**
* @class Card, the concrete implementation for cards
*/
class Card {
public:
	/**
	* @brief Enumeration for Card Ranks
	*/
	enum Rank {
		Zero, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		Ten, Jack, Queen, King, Skip, Reverse, Draw2, SwitchColor, Draw4
	};

	/**
	* @brief Enumeration for the Card Face
	*/
	enum Face {
		Yellow, Blue, Green, Red, Wild, RedHeart, RedDiamond, BlackSpade, BlackClub
	};

	/**
	* Constructor for a Card Object
	* @param r is the Rank of the Card
	* @param f is the Face of the Card
	* @return a card object
	*/
	Card(Rank r = Ace, Face f = BlackSpade) : cardRank{ r }, cardFace{ f } {}

	virtual ~Card() {}

	/**
	* Setter for Card Rank
	* @param r is the Rank to set
	*/
	void setRank(const Rank& r);

	/**
	* Getter to get the Card's Rank
	* @return the Card's Rank
	*/
	Rank getRank();

	/**
	* Setter for Card Face
	* @param f is the Face to set
	*/
	void setFace(const Face& f);

	/**
	* Getter to get the Card's Face
	* @return the Card's Rank
	*//**
  * @author Blake McLachlin
  * @date November 23, 2018
  */

	Face getFace();

	/**
	* Displays card
	* @return an output stream containing a representation of the card
	*  a "Face:Rank format"
	*/
	friend std::ostream& operator<<(std::ostream& os, Card& c);

	/**
	* Print a card enum value for save file
	*/
	std::ostream& printCard(std::ostream& os);

	/**
	* Overloaded equals operator
	*/
	bool operator==(const Card& c1);

	/**
	* Overloaded assignment operator
	*/
	Card& operator=(const Card& c);

protected:
	Rank cardRank;
	Face cardFace;
	const char *Rank_str[19] = { "Zero", "Ace", "Two", "Three",
	 "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
	  "Jack", "Queen", "King", "Skip", "Reverse", "Draw2",
	   "SwitchColor", "Draw4" };
	const char *Face_str[9] = { "Yellow", "Blue", "Green",
	 "Red", "Wild", "RedHeart", "RedDiamond",
	 "BlackSpade", "BlackClub" };
};

#endif // CARD
