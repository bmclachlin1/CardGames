/**
* @author Cassady Campos
* @date November 6 2018
*/

#include "goFish.h"
#include "drawPile.h"
#include "playerHand.h"
#include "discardPile.h"
#include <string>

/**
* Constructor for a goFish game
* initializes all the decks and deals the cards out
*/
goFish::goFish() {
	Deck = new drawPile(1);
	PlayerHand = new playerHand();
	ComputerHand = new playerHand();
	DiscardPile = new discardPile();
	playerScore = 0;
	computerScore = 0;
}

/**
* Destructor for a goFish game
* deallocates all the memory made
*/
goFish::~goFish() {
	delete Deck;
	Deck = nullptr;
	delete PlayerHand;
	PlayerHand = nullptr;
	delete ComputerHand;
	ComputerHand = nullptr;
	delete DiscardPile;
	DiscardPile = nullptr;
}

/**
* @brief Loads the game by first deallocating all the memory
*  created when the goFish object was first created.
*  Then we read in from the file allocating the new cards into
*  their respective decks and record the scores.
*/
void goFish::loadGame() {
	int cFace;
	int cRank;
	int numOfCards;
	std::string cardInfo;

	std::cout << "Loading Game" << std::endl;
	std::ifstream fin;
	fin.open("goFish.dat");

	if (fin.is_open()) {
		/*
		//* Release current memory of cards
		delete Deck;
		Deck = nullptr;
		delete PlayerHand;
		PlayerHand = nullptr;
		delete ComputerHand;
		ComputerHand = nullptr;
		delete DiscardPile;
		DiscardPile = nullptr;
		//* Allocate memory for the incoming data
		Deck = new drawPile(1);
		PlayerHand = new playerHand();
		ComputerHand = new playerHand();
		DiscardPile = new discardPile();
	*/
	//* Load the Deck
		fin >> numOfCards;
		fin.ignore(100, '\n');
		for (int i = 0; i < numOfCards; i++) {
			Card* temp = new Card;
			fin >> cardInfo;
			cFace = atoi(cardInfo.c_str());
			cRank = atoi(cardInfo.substr(2, 2).c_str());
			temp->setFace(Card::Face(cFace));
			temp->setRank(Card::Rank(cRank));
			Deck->insertCard(temp);
		}
		fin.ignore(100, '\n');

		//* Load Player's Hand
		fin >> numOfCards;
		fin.ignore(100, '\n');
		for (int i = 0; i < numOfCards; i++) {
			Card* temp = new Card;
			fin >> cardInfo;
			cFace = atoi(cardInfo.c_str());
			cRank = atoi(cardInfo.substr(2, 2).c_str());
			temp->setFace(Card::Face(cFace));
			temp->setRank(Card::Rank(cRank));
			PlayerHand->insertCard(temp);
		}
		fin.ignore(100, '\n');

		//* Load Computer's Hand
		fin >> numOfCards;
		fin.ignore(100, '\n');
		for (int i = 0; i < numOfCards; i++) {
			Card* temp = new Card;
			fin >> cardInfo;
			cFace = atoi(cardInfo.c_str());
			cRank = atoi(cardInfo.substr(2, 2).c_str());
			temp->setFace(Card::Face(cFace));
			temp->setRank(Card::Rank(cRank));
			ComputerHand->insertCard(temp);
		}
		fin.ignore(100, '\n');

		//* Load Player's Score
		fin >> numOfCards;
		playerScore = numOfCards;
		fin.ignore(100, '\n');

		//* Load Computer's Score
		fin >> numOfCards;
		computerScore = numOfCards;

		fin.close();
	}
	else {
		std::cout << "No save file present. Returning to game menu.\n";
		playGame();
	}
}

/**
* @brief Saves the game to an output file by loading all the
*  decks, hands and scores.
*/
void goFish::saveGame() {
	Card temp;
	std::cout << "Saving Game" << std::endl;
	std::ofstream out("goFish.dat");

	//* Save the Deck
	out << Deck->getSize() << " Cards in the Deck******" << std::endl;
	for (int i = 0; i < Deck->getSize(); i++) {
		temp = Deck->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the PlayerHand
	out << PlayerHand->getSize() << " Cards in the Player's Hand******\n";
	for (int i = 0; i < PlayerHand->getSize(); i++) {
		temp = PlayerHand->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the OpponentHand
	out << ComputerHand->getSize() << " Cards in the Computer's Hand******\n";
	for (int i = 0; i < ComputerHand->getSize(); i++) {
		temp = ComputerHand->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the playerScore
	out << getPlayerScore() << " Is the Player's Score******" << std::endl;
	//* Save the computerScore
	out << getComputerScore() << " Is the Computer's Score******" << std::endl;

	out.close();
}

/**
* Initiated once the user starts a new game or loads a game.
* Game always starts on the player's turn.
*/
void goFish::playGame() {
	int fishMenu = menu();

	switch (fishMenu) {
	case 1:
		Deck->deal(PlayerHand, ComputerHand);
		while (endGame() == false) {
			std::cout << std::endl;
			showScores();
			std::cout << std::endl;
			playTurn();
			computerTurn();
			std::cout << "Cards left in deck: " << Deck->getSize() << std::endl;
			saveGame();
		}
		std::cout << "****GAME OVER! NO MORE CARDS TO DRAW!****" << std::endl;
		declareWinner();
		break;
	case 2:
		loadGame();
		while (endGame() == false) {
			std::cout << std::endl;
			showScores();
			std::cout << std::endl;
			playTurn();
			if (endGame() == true) {
				std::cout << "****GAME OVER! NO MORE CARDS TO DRAW!****" << std::endl;
				declareWinner();
			}
			computerTurn();
			std::cout << "Cards left in deck: " << Deck->getSize() << std::endl;
			saveGame();
		}
		std::cout << "****GAME OVER! NO MORE CARDS TO DRAW!****" << std::endl;
		declareWinner();
	case 3:
		helperFunc();
	case 4:
		exit(0);
	default:
		std::cout << "Invalid option. Try again. \n";
	}
}

/**
* Displays the menu for a game of Uno
* @return the choice of the user
*/
int goFish::menu() {
	int choice;
	std::cout << "\nGo Fish Menu" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Help" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cin >> choice;
	return choice;
}

/**
* A human players turn sequence.
*/
void goFish::playTurn() {
	bool askAgain = true;
	int pos;
	Card* cptr;

	if (PlayerHand->isEmpty() == 1 && Deck->isEmpty() == 0) {
		std::cout << "***Your hand was empty, so you drew a ";
		cptr = Deck->getAt(rand() % (Deck->getSize()) + 0);
		Deck->moveCard(PlayerHand, cptr);
		std::cout << (*cptr) << " from the deck.\n";
	}

	while (askAgain == true) {
		if (PlayerHand->isEmpty() == 1 && Deck->isEmpty() == 0) {
			std::cout << "***Your hand was empty, so you drew a ";
			cptr = Deck->getAt(rand() % (Deck->getSize()) + 0);
			Deck->moveCard(PlayerHand, cptr);
			std::cout << (*cptr) << " from the deck.\n";
		}

		if (PlayerHand->isEmpty() == 1 && ComputerHand->isEmpty() == 1
			&& Deck->isEmpty() == 1)
			return;

		std::cout << "***Computer Hand***" << std::endl;
		ComputerHand->show();
		std::cout << "\n";
		std::cout << "***Your Hand of " << PlayerHand->getSize() << "***\n";
		PlayerHand->show();


		std::cout << "Select a card with the Rank you want to ask" << std::endl;
		std::cin >> pos;
		while (!std::cin || pos < 0 || pos > PlayerHand->getSize() - 1) {
			std::cout << "Please choose a valid option. \n";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> pos;
		}


		cptr = PlayerHand->getAt(pos);

		if (ComputerHand->containsRank(cptr) == 1) {
			do {
				ComputerHand->moveCard(PlayerHand, ComputerHand->getRankAt(cptr));
				cptr = PlayerHand->getAt(PlayerHand->getSize() - 1);
				std::cout << "******YAY, you've received " << (*cptr) << "******\n";
			} while (ComputerHand->containsRank(cptr));
		}
		else {
			if (Deck->isEmpty() == 1) {
				return;
			}
			cptr = Deck->getAt(rand() % (Deck->getSize()) + 0);
			Deck->moveCard(PlayerHand, cptr);
			std::cout << "******You Go Fish and Receive " << (*cptr) << "******\n";
			askAgain = false;
		}
		checkForSet();
	}
}

/**
* Function which programs how a computer will play a turn
*/
void goFish::computerTurn() {
	std::cout << "Computer's turn" << std::endl;
	bool askAgain = true;
	Card* cptr;

	if (ComputerHand->isEmpty() == 1 && Deck->isEmpty() == 0) {
		std::cout << "***Computer's hand was empty so they drew\n";
		cptr = Deck->getAt(rand() % (Deck->getSize()) + 0);
		Deck->moveCard(ComputerHand, cptr);
	}

	checkComputer();
	while (askAgain == true) {
		if (PlayerHand->isEmpty() == 1 && ComputerHand->isEmpty() == 1
			&& Deck->isEmpty() == 1)
			return;
		for (int i = 0; i < ComputerHand->getSize(); i++) {
			cptr = ComputerHand->getAt(i);
			if (PlayerHand->containsRank(cptr) == 1) {
				std::cout << "***Computer's asking for his card at index "
					<< i << "***\n";
				do {
					PlayerHand->moveCard(ComputerHand, PlayerHand->getRankAt(cptr));
					cptr = ComputerHand->getAt(ComputerHand->getSize() - 1);
					std::cout << "***Oh no! The Computer stole your " << (*cptr)
						<< "***\n";
				} while (PlayerHand->containsRank(cptr));
				checkComputer();
				return;
			}
			if (Deck->isEmpty() == 1) {
				return;
			}
		}
		cptr = Deck->getAt(rand() % (Deck->getSize()) + 0);
		Deck->moveCard(ComputerHand, cptr);
		std::cout << "*******Computer had to Go Fish*******" << std::endl;
		askAgain = false;
	}
	checkComputer();
}

/**
* Checks every time the player adds a card to his hand if he has
* a four of a kind, if they have increase the player's score.
*/
void goFish::checkForSet() {
	int counter;
	int firstCard;

	//* Check Hand for four of a Kind's
	for (int i = 0; i < PlayerHand->getSize(); i++) {
		counter = 1;
		for (int j = i + 1; j < PlayerHand->getSize(); j++) {
			if (PlayerHand->getAtCard(i).getRank() ==
				PlayerHand->getAtCard(j).getRank())
				counter++;
			//*If we reached four of a kind, remember the
			//initial cards position and increase our score
			if (counter == 4) {
				firstCard = i;
				//* Delete the four of a kind the initial position, deleting from the bottom up
				for (int k = (PlayerHand->getSize()) - 1; k > firstCard; k--) {
					if (PlayerHand->getAtCard(firstCard).getRank() ==
						PlayerHand->getAtCard(k).getRank()) {
						PlayerHand->moveCard(DiscardPile, PlayerHand->getAt(k));
					}
				}
				PlayerHand->moveCard(DiscardPile, PlayerHand->getAt(firstCard));
				std::cout << "***CONGRATS you got four of a kind***" << std::endl;
				playerScore++;
			}
		}
	}
}

/**
* Checks every time the computer adds a card to his hand if he has
* a four of a kind, if they have increase the computer's score.
*/
void goFish::checkComputer() {
	int counter;
	int firstCard;

	//* Check Hand for four of a Kind's
	for (int i = 0; i < ComputerHand->getSize(); i++) {
		counter = 1;
		for (int j = i + 1; j < ComputerHand->getSize(); j++) {
			if (ComputerHand->getAtCard(i).getRank() ==
				ComputerHand->getAtCard(j).getRank())
				counter++;
			//*If we reached four of a kind, remember the
			//initial cards position and increase our score
			if (counter == 4) {
				firstCard = i;
				//* Delete the four of a kind the initial position, deleting from the bottom up
				for (int k = (ComputerHand->getSize()) - 1; k > firstCard; k--) {
					if (ComputerHand->getAtCard(firstCard).getRank() ==
						ComputerHand->getAtCard(k).getRank()) {
						ComputerHand->moveCard(DiscardPile, ComputerHand->getAt(k));
					}
				}
				ComputerHand->moveCard(DiscardPile, ComputerHand->getAt(firstCard));
				std::cout << "***OH NO! The computer got four of a kind***"
					<< std::endl;
				computerScore++;
			}
		}
	}
}
/**
* Determines when the game is over.
* @return True if an end condition for the game has been met, false
* otherwise.
*/
bool goFish::endGame() {
	if (Deck->isEmpty() == 1)
		return true;

	return false;
}

/**
* Show the score of both players at every turn
*/
void goFish::showScores() {
	std::cout << "Your Score: " << playerScore
		<< "\nComputer Score: " << computerScore << std::endl;
}

/**
* Getter function for the player's score
*/
int goFish::getPlayerScore() {
	return playerScore;
}

/**
* Getter function for the computer's score
*/
int goFish::getComputerScore() {
	return computerScore;
}

/**
* Displays the winner
*/
void goFish::declareWinner() {
	std::cout << "FINAL SCORES" << std::endl;
	std::cout << "You: " << getPlayerScore() << std::endl;
	std::cout << "Computer: " << getComputerScore() << std::endl;
	if (playerScore == computerScore) {
		std::cout << "GAME ENDED IN A DRAW!" << std::endl;
	}
	else if (playerScore > computerScore) {
		std::cout << "YOU WIN!" << std::endl;
	}
	else {
		std::cout << "YOU LOST!" << std::endl;
	}
}

/**
* When called explains the rules of the game go Fish
*/
void goFish::helperFunc() {
	char choice;
	std::cout << "\n***RULES & HOW TO PLAY GO FISH***\n"
		<< "The point of GoFish is to collect as many four\n"
		<< "of a kind's as possible. You collect four a kind's\n"
		<< "by asking the computer for a certain Rank with one of\n"
		<< "the cards in your hand. If the computer has any cards of\n"
		<< "the same rank, you will receive them, if not then you\n"
		<< "will goFish meaning you will draw from the deck.\n"
		<< "After your turn the computer will perform the same\n"
		<< "action. The game ends when there are no more cards\n"
		<< "left to draw from the deck and a winner is declared.\n"
		<< "Do you wish to play now? (Y/N) ";
	std::cin >> choice;
	switch (toupper(choice)) {
	case 'Y':
		playGame();
		break;
	case 'N':
		std::cout << "\nLeaving program.\n";
		break;
	}
}
