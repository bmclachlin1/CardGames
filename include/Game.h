/**
* @author Prosper Ibhamawu
* @date November 1 2018
*/
#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>
#include <string>
#include "cardCollection.h"

/**
* @class Game is the abstract base class drawPile, discardPile, and playerHand
*/
class Game {
	friend class cardCollection;
public:
	Game() {}
	virtual ~Game() {}

	virtual void loadGame() = 0;
	virtual void saveGame() = 0;
	virtual void playGame() = 0;
	virtual void playTurn() = 0;
	virtual void computerTurn() = 0;
	virtual bool endGame() = 0;
	virtual int menu() = 0;
	virtual void helperFunc() = 0;
	cardCollection* getDeck();
	cardCollection* getPlayerHand();
	cardCollection* getComputerHand();
	cardCollection* getDiscardPile();

protected:
	/**< Pointer to the pile the players draw from*/
	cardCollection* Deck;
	/**< Pointer to the users hand*/
	cardCollection* PlayerHand;
	/**< Pointer to the CPU's hand*/
	cardCollection* ComputerHand;
	/**< Pointer to the discard pile*/
	cardCollection* DiscardPile;
};
#endif // GAME_H
