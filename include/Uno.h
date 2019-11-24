/**
* @author Blake McLachlin
* @date November 7, 2018
*/

#ifndef UNO_H
#define UNO_H

#include "Game.h"

/**
* @class Uno, which is the implementation
* of the abstract class Game for an Uno game
*/
class Uno : public Game {
public:
	Uno();
	~Uno();

	/**
	* Loads the game
	*/
	void loadGame();

	/**
	* Saves the game
	*/
	void saveGame();

	/**
	* Initiated once the user starts a new game or loads a game.
	* Game always starts on the player's turn.
	*/
	void playGame();

	/**
	* Function which allows a user to play a turn
	*/
	void playTurn();

	/**
	* Function which programs how a computer will play a turn
	*/
	void computerTurn();

	/**
	* Determines when the game is over.
	* @return True if someone has won (the game is over). False
	* otherwise
	*/
	bool endGame();

	/**
	* Displays the menu for a game of Uno
	* @return the choice of the user
	*/
	int menu();

	/**
	* Checks that the player can actually make a move
	* place a card in the discard pile)
	* @param c the card collection that is being checked for a valid move
	* @return true if the player has a move
	*/
	bool hasMove(cardCollection* c);

	/**
	* Switches the face of the wild card being played
	* @param c the card that's getting its face switched
	*/
	void switchFace(Card *c);

	/**
	* stub function. This function was pure virtual in Game.h
	* but is not needed for uno so the implementation is empty
	*/
	void helperFunc() {}

protected:
	/**<Points to the last card played*/
	Card* state;
	/**<True if it's the player's turn. False if computer's turn*/
	bool playersTurn;
};

#endif //UNO_H
