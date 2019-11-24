/**
* @author Blake McLachlin
* @date November 7, 2018
*/

#ifndef CRAZYEIGHTS_H
#define CRAZYEIGHTS_H
#include "Game.h"

/**
* @class crazyEights which is the implementation
* of the abstract class game for a crazy eights game
*/
class crazyEights : public Game {
public:
	/**
	* This is the crazy Eights game constructor
	*/
	crazyEights();

	/**
	* This deallocates the memory from the construction of the game
	*/
	~crazyEights();

	/**
	* This is the loading game
	*/
	void loadGame();

	/**
	* Overloaded assignment operator
	*/
	void saveGame();

	/**
	* simulation of the game for the human
	*/
	void playTurn();

	/**
	* Checks if the card about to be played has matching face with center pile
	* @param play the card being played. Center, the card in the center pile
	* @return true if the card about to be played have matching Faces, Otherwise, false
	*/
	bool checkFace(Card* play, Card* center);

	/**
	* Checks if the card about to be played has matching rank with center pile
	* @param play the card about to be played. center, the card in the center pile
	* @return true if the card about to be played have matching Ranks, Otherwise, false
	*/
	bool checkRank(Card* play, Card* center);

	/**
	* Checks if the user has a valid move they can make
	* @param c the cardCollection that is being checked for a valid move
	* @return true if the card about to be played is plausible, Otherwise, false
	*/
	bool hasMove(cardCollection* c);

	/**
	* Determines if the game is over
	* @return true if the either player or computer hand is empty
	*/
	bool endGame();

	/**
	* Displays the menu for a game of CrazyEights
	* @return the choice of the user
	*/
	int menu();

	/**
	* Simulation of computer playing style
	*/
	void computerTurn();

	/**
	* Winning conditions
	*/
	void winGame();

	/**
	* Holds the sub menu for the crazy Eights game and various in-game selections
	*/
	void playGame();

	/**
	* Switches the center card to requested card
	* @param c the card you're trying to match face with
	*/
	void switchFace(Card* c);

	/**
	* Switches the center card to requested card for the computer
	* @param c the card you're trying to match face with
	*/
	void switchCompFace(Card* c);

	/**
	* when called gives you info of the game
	*/
	void helperFunc();

protected:
};

#endif // CRAZYEIGHTS_H
