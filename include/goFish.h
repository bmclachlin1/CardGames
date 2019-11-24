/**
* @author Cassady Campos
* @date November 6, 2018
*/
#ifndef GOFISH_H
#define GOFISH_H
#include <fstream>
#include "Game.h"

/**
* @class goFish, which is the implementation
* of the abstract class game for a go fish game
*/
class goFish : public Game {
	friend class cardCollection;
public:
	goFish();
	~goFish();

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
	* A human players turn sequence.
	*/
	void playTurn();

	/**
	* Function which programs how a computer will play a turn
	*/
	void computerTurn();

	/**
	* Determines when the game is over.
	* @return True if an end condition for the game has been met, false
	* otherwise.
	*/
	bool endGame();

	/**
	* Displays the menu for a game of Uno
	* @return the choice of the user
	*/
	int menu();

	/**
	* Checks our hand if we scored a four of a kind
	* If we did, remove those cards from our hand and increase score
	*/
	void checkForSet();

	/**
	* Checks computer hand if they scored four of a kind
	* If the computer did, remove those cards from it's hand
	* and increase score
	*/
	void checkComputer();
	/**
	* Show the score of both players at every turn
	*/
	void showScores();

	/**
	* Getter function for the player's score
	* @return the players score
	*/
	int getPlayerScore();

	/**
	* Getter function for the computer's score
	* @return the computers score
	*/
	int getComputerScore();

	/**
	* Displays the winner
	*/
	void declareWinner();

	/**
	* When called explains the rules of the game
	*/
	void helperFunc();

protected:
	/**< The players score*/
	int playerScore;
	/**< The computers score*/
	int computerScore;
};
#endif // GOFISH_H
