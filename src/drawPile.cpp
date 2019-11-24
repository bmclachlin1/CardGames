/**
* @author Blake McLachlin
* @date November 4, 2018
*/

#include "drawPile.h"

/**
* @brief if game = 1 || 2 we create standard deck, otherwise we create Uno deck
*/
drawPile::drawPile(const int& game) :cardCollection() {
	int deckPos = 0;
	if (game == 1 || game == 2) {
		this->sizeOf = 52;
		while (deckPos < 52) {
			for (int i = 1; i < 14; i++)
				for (int j = 5; j < 9; j++) {
					this->deck.push_back(new Card(static_cast<Card::Rank>(i),
						static_cast<Card::Face>(j)));
					deckPos++;
				}
		}
	}
	else if (game == 3) {
		this->sizeOf = 108;
		while (deckPos < 108) {
			//* Create 0's
			for (int j = 0; j <= 3; j++) {
				this->deck.push_back(new Card(static_cast<Card::Rank>(0),
					static_cast<Card::Face>(j)));
				deckPos++;
			}

			//* Create 1 - 9's
			for (int repeat = 0; repeat < 2; repeat++) {
				for (int i = 1; i <= 9; i++)
					for (int j = 0; j <= 3; j++) {
						this->deck.push_back(new Card(static_cast<Card::Rank>(i),
							static_cast<Card::Face>(j)));
						deckPos++;
					}
			}

			//* Create special colored cards skip, reverse, draw2
			for (int repeat = 0; repeat < 2; repeat++) {
				for (int i = 14; i <= 16; i++)
					for (int j = 0; j <= 3; j++) {
						this->deck.push_back(new Card(static_cast<Card::Rank>(i),
							static_cast<Card::Face>(j)));
						deckPos++;
					}
			}
			//* Create Wild cards
			for (int repeat = 0; repeat < 4; repeat++) {
				for (int i = 17; i <= 18; i++) {
					this->deck.push_back(new Card(static_cast<Card::Rank>(i),
						static_cast<Card::Face>(4)));
					deckPos++;
				}
			}
		}

	}
	else {
		std::cerr << "some throw message\n";
	}
}

void drawPile::show() {
	//empty method. A player should not be able
	//to see the drawPile because it is face down
}

void drawPile::deal(cardCollection *H, cardCollection *C) {
	srand( static_cast<unsigned int>(time(NULL)) );

	if (this->getSize() == 52) {
		for (int i = 0; i < 7; i++)
			moveCard(H, deck[rand() % (51 - i) + 0]);

		for (int i = 0; i < 7; i++)
			moveCard(C, deck[rand() % (44 - i) + 0]);
	}
	else if (this->getSize() == 108) {
		for (int i = 0; i < 7; i++)
			moveCard(H, deck[rand() % (107 - i) + 0]);

		for (int i = 0; i < 7; i++)
			moveCard(C, deck[rand() % (100 - i) + 0]);
	}
}
