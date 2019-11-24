/**
* @author Blake McLachlin
* @date November 7, 2018
*/

#include "Uno.h"
#include "drawPile.h"
#include "playerHand.h"
#include "cardCollection.h"
#include "card.h"
#include "discardPile.h"
#include <cstdlib>
#include <string>
#include <fstream>

Uno::Uno() {
	Deck = new drawPile(3);
	PlayerHand = new playerHand();
	ComputerHand = new playerHand();
	DiscardPile = new discardPile();
	Deck->deal(PlayerHand, ComputerHand);
}

Uno::~Uno() {
	delete Deck;
	Deck = nullptr;
	delete PlayerHand;
	PlayerHand = nullptr;
	delete ComputerHand;
	ComputerHand = nullptr;
	delete DiscardPile;
	DiscardPile = nullptr;
	delete state;
	state = nullptr;
}

void Uno::loadGame() {
	int cFace;
	int cRank;
	int numOfCards;
	std::string cardInfo;

	//* Release current memory of cards
	delete DiscardPile;
	DiscardPile = nullptr;


	//* Allocate memory for the incoming data
	Deck = new drawPile(3);
	PlayerHand = new playerHand();
	ComputerHand = new playerHand();
	DiscardPile = new discardPile();

	std::ifstream fin;
	fin.open("Uno.dat");

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

	//* Load the Player's Hand
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
	fin.ignore(100, '\n');

	//* Load the Discard Pile's card
	Card* temp = new Card;
	fin >> cardInfo;
	cFace = atoi(cardInfo.c_str());
	cRank = atoi(cardInfo.substr(2, 2).c_str());
	temp->setFace(Card::Face(cFace));
	temp->setRank(Card::Rank(cRank));
	DiscardPile->insertCard(temp);
}

void Uno::saveGame() {
	Card temp;
	std::cout << "Saving Game. . ." << std::endl;
	std::ofstream out("Uno.dat");

	//* Save the deck
	out << Deck->getSize() << " Cards in the Deck*******" << std::endl;
	for (int i = 0; i < Deck->getSize(); i++) {
		temp = Deck->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the Player's Hand
	out << PlayerHand->getSize() << " Card in the Player's Hand******"
		<< std::endl;
	for (int i = 0; i < PlayerHand->getSize(); i++) {
		temp = PlayerHand->getAtCard(i);
		temp.printCard(out);
	}
	out << ComputerHand->getSize()
		<< " Cards in the Computer's Hand******" << std::endl;
	for (int i = 0; i < ComputerHand->getSize(); i++) {
		temp = ComputerHand->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the Last card played
	out << DiscardPile->getSize()
		<< "Cards in the Discard Pile******" << std::endl;
	temp = DiscardPile->getAtCard(DiscardPile->getSize() - 1);
	temp.printCard(out);

	out.close();
}

int Uno::menu() {
	int choice = 0;
	while
		(!std::cin || (choice != 1 && choice != 2 && choice != 3 && choice != 4)) {
		std::cout << "\nWelcome to Uno!" << std::endl;
		std::cout << "1. New Game" << std::endl;
		std::cout << "2. Load Game" << std::endl;
		std::cout << "3. Help" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore();
	}
	return choice;
}

void Uno::playGame() {
	playersTurn = true;

	srand( static_cast<unsigned int>(time(NULL)) );
	int randIndex = rand() % Deck->getSize();
	Deck->moveCard(DiscardPile, Deck->getAt(randIndex));
	state = DiscardPile->getAt(0);

	int unoMenu;
	do {
		unoMenu = menu();
		switch (unoMenu) {
		case 1:
			while (!endGame()) {
				if (playersTurn == true)
					playTurn();
				else {
					computerTurn();
					saveGame();
				}
				if (playersTurn == true)
					playersTurn = false;
				else
					playersTurn = true;
			}
			break;
		case 2:
			loadGame();
			while (!endGame()) {
				if (playersTurn == true)
					playTurn();
				else {
					computerTurn();
					computerTurn();
					saveGame();
				}
				if (playersTurn == true)
					playersTurn = false;
				else
					playersTurn = true;
			}
			break;
		case 3: {
			std::ifstream fileIn;
			fileIn.open("UnoHelp.dat");
			std::string output;
			if (fileIn.is_open()) {
				while (!fileIn.eof()) {
					std::getline(fileIn, output);
					std::cout << output;
					std::cout << std::endl;
				}
			}
			fileIn.close();
			break;
		}
		case 4:
			std::cout << "Exiting the program . . . \n";
			exit(0);
			break;
		default:
			std::cout << "Invalid option. Try again. \n";
			break;
		}
	} while (unoMenu == 3);
}

void Uno::playTurn() {
	if (PlayerHand->getSize() == 1)
		std::cout << "You have one card left! UNO!\n\n";
	Card* played;
	int pos;
	std::cout << "Last Card Played:\n";
	DiscardPile->show();
	std::cout << "\n";
	std::cout << "Your Hand:\n";
	PlayerHand->show();

	if (hasMove(PlayerHand)) {
		std::cout << "Pick A card to play!\n";
		std::cin >> pos;
		while (!std::cin || pos < 0 || pos > PlayerHand->getSize() - 1) {
			std::cout << "Please choose a valid option \n";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> pos;
		}

		played = PlayerHand->getAt(pos);
		if ((played->getRank() == state->getRank() || played->getFace() ==
			state->getFace()) || played->getRank() > 16 || state->getFace() == 4) {
			PlayerHand->moveCard(DiscardPile, played);
			if (played->getRank() == 14)
				playersTurn = false;
			else if (played->getRank() == 16) {
				std::cout << "The CPU draws 2 cards!\n\n";
				int randIndex;
				for (int i = 0; i < 2; i++) {
					srand( static_cast<unsigned int>(time(NULL)) );
					randIndex = rand() % Deck->getSize();
					Deck->moveCard(ComputerHand, Deck->getAt(randIndex));
				}
			}
			else if (played->getRank() == 18) {
				int randIndex;
				std::cout << "The CPU draws 4 cards!\n\n";
				for (int i = 0; i < 4; i++) {
					srand( static_cast<unsigned int>(time(NULL)) );
					randIndex = rand() % Deck->getSize();
					Deck->moveCard(ComputerHand, Deck->getAt(randIndex));
				}
				switchFace(played);
			}
			else if (played->getRank() == 17) {
				switchFace(played);
			}
			state = played;
		}
		else
			std::cout << "Invalid option... ending turn\n\n";
	}
	else {
		std::cout << "You have nothing to play. Drawing a card...\n\n";
		srand( static_cast<unsigned int>(time(NULL)) );
		int randIndex = rand() % Deck->getSize();
		Deck->moveCard(PlayerHand, Deck->getAt(randIndex));
	}
}

void Uno::computerTurn() {
	if (ComputerHand->getSize() == 1)
		std::cout << "Computer has one card left! UNO!\n\n";
	Card* played;
	std::cout << "Last Card Played:\n";
	DiscardPile->show();
	std::cout << "\n";

	if (hasMove(ComputerHand)) {
		for (int i = 0; i < ComputerHand->getSize(); i++) {
			played = ComputerHand->getAt(i);
			if (played->getRank() == state->getRank() || played->getFace()
				== state->getFace() || played->getRank() > 16
				|| played->getFace() == 4) {
				ComputerHand->moveCard(DiscardPile, played);
				if (played->getRank() == 14)
					playersTurn = true;
				else if (played->getRank() == 16) {
					std::cout << "You draw 2 cards!\n\n";
					int randIndex;
					for (int i = 0; i < 2; i++) {
						srand( static_cast<unsigned int>(time(NULL)) );
						randIndex = rand() % Deck->getSize();
						Deck->moveCard(PlayerHand, Deck->getAt(randIndex));
					}
				}
				else if (played->getRank() == 18) {
					int randIndex;
					int faceChange;
					std::cout << "You draw 4 cards!\n\n";
					for (int i = 0; i < 4; i++) {
						srand(static_cast<unsigned int>(time(NULL)));
						randIndex = rand() % Deck->getSize();
						Deck->moveCard(PlayerHand, Deck->getAt(randIndex));
					}
					srand(static_cast<unsigned int>(time(NULL)));
					faceChange = rand() % 4;
					played->setFace(static_cast<Card::Face>(faceChange));
				}
				else if (played->getRank() == 17) {
					int faceChange;
					srand(static_cast<unsigned int>(time(NULL)));
					faceChange = rand() % 4;
					played->setFace(static_cast<Card::Face>(faceChange));
				}
				state = played;
				std::cout << "CPU played a card! \n";
				std::cout << "CPU has " << ComputerHand->getSize()
					<< " cards in its hand.\n\n";
				break;
			}
		}
	}
	else {
		std::cout << "CPU has nothing to play. Drawing a card...\n";
		srand(static_cast<unsigned int>(time(NULL)));
		int randIndex = rand() % Deck->getSize();
		Deck->moveCard(ComputerHand, Deck->getAt(randIndex));
		std::cout << "CPU has " << ComputerHand->getSize()
			<< " cards in its hand.\n\n";
	}
}

bool Uno::hasMove(cardCollection* c) {
	for (int i = 0; i < c->getSize(); i++)
		if (c->getAtCard(i).getRank()
			== DiscardPile->getAt(DiscardPile->getSize() - 1)->getRank()
			|| c->getAtCard(i).getFace() ==
			DiscardPile->getAt(DiscardPile->getSize() - 1)->getFace()
			|| c->getAtCard(i).getFace() == Card::Face(4))
			return true;
	return false;
}

bool Uno::endGame() {
	if (PlayerHand->isEmpty()) {
		std::cout << "You Won! \n";
		return true;
	}
	else if (ComputerHand->isEmpty()) {
		std::cout << "The CPU Won! \n";
		return true;
	}
	else if (Deck->isEmpty()) {
		std::cout << "The Draw Pile ran out of cards! It's a draw! \n";
		return true;
	}
	return false;
}

void Uno::switchFace(Card* c) {
	int color = 10;
	while (!std::cin || (color != 0 && color != 1 && color != 2 && color != 3)) {
		std::cout << "Choose a color to switch to!\n";
		std::cout << "0: Yellow\n1: Blue\n2: Green\n3: Red\n";
		std::cin >> color;
	}
	switch (color) {
	case 0:
		c->setFace(Card::Yellow);
		std::cout << "Card is now: Yellow\n";
		break;
	case 1:
		c->setFace(Card::Blue);
		std::cout << "Card is now: Blue\n";
		break;
	case 2:
		c->setFace(Card::Green);
		std::cout << "Card is now: Green\n";
		break;
	case 3:
		c->setFace(Card::Red);
		std::cout << "Card is now: Red\n";
		break;
	}
}

