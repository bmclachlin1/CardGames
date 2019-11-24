/**
* @author Blake McLachlin
* @date November 7, 2018
*/

#include "crazyEights.h"
#include "drawPile.h"
#include "playerHand.h"
#include "discardPile.h"
#include <vector>
#include <string>

crazyEights::crazyEights() {
	Deck = new drawPile(2);
	PlayerHand = new playerHand();
	ComputerHand = new playerHand();
	DiscardPile = new discardPile();
	Deck->deal(PlayerHand, ComputerHand);
}

crazyEights::~crazyEights() {
	delete Deck;
	Deck = nullptr;
	delete PlayerHand;
	PlayerHand = nullptr;
	delete ComputerHand;
	ComputerHand = nullptr;
	delete DiscardPile;
	DiscardPile = nullptr;
}

void crazyEights::loadGame() {
	int cFace;
	int cRank;
	int numOfCards;
	std::string cardInfo;

	std::cout << "Loading Game" << std::endl;
	std::ifstream fin;
	fin.open("crazyEight.dat");

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
			Deck = new drawPile(2);
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

		fin.close();
	}
	else {
		std::cout << "No save file present. Returning to game menu.\n";
		playGame();
	}
}

void crazyEights::saveGame() {
	Card temp;
	std::cout << "Saving Game" << std::endl;
	std::ofstream out("crazyEight.dat");

	//* Save the deck
	out << Deck->getSize() << " Cards in the Deck*******" << std::endl;
	for (int i = 0; i < Deck->getSize(); i++) {
		temp = Deck->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the Player's Hand
	out << PlayerHand->getSize() << " Card in the Player's Hand******\n";
	for (int i = 0; i < PlayerHand->getSize(); i++) {
		temp = PlayerHand->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the Opponent's Hand
	out << ComputerHand->getSize() << " Cards in the Computer's Hand******\n";
	for (int i = 0; i < ComputerHand->getSize(); i++) {
		temp = ComputerHand->getAtCard(i);
		temp.printCard(out);
	}
	//* Save the Last card played
	out << DiscardPile->getSize() << " Cards in the Discard Pile******\n";
	temp = DiscardPile->getAtCard(DiscardPile->getSize() - 1);
	temp.printCard(out);
	out.close();
}

void crazyEights::playTurn() {
	Card* gamestate;
	Card* centerCard;
	Card* drawCard;
	int pos;

	std::cout << "**Computer Hand**" << ComputerHand->getSize() << "***\n";
	std::cout << std::endl;
	//Deck->moveCard(DiscardPile, startCard);
	std::cout << "***Discard Pile " << DiscardPile->getSize() << "***\n";
	DiscardPile->show();
	std::cout << "\n***Your Hand of " << PlayerHand->getSize() << "***\n";
	PlayerHand->show();
	std::cout << "choose a number to play or draw if you do not have the card: ";
	std::cin >> pos;
	std::cout << std::endl;

	while (!std::cin || pos < 0 || pos > PlayerHand->getSize() - 1) {
		std::cout << "Please choose a valid option \n";
		std::cin.clear();
		std::cin.ignore();
		std::cin >> pos;
	}

	gamestate = PlayerHand->getAt(pos);
	centerCard = DiscardPile->getAt(DiscardPile->getSize() - 1);
	drawCard = Deck->getAt(rand() % (Deck->getSize()) + 0);

	bool Rank = checkRank(gamestate, centerCard);
	bool Face = checkFace(gamestate, centerCard);
	if (Rank || Face) {
		std::cout << "***YOU PLAYED A CARD***\n";
		std::cout << std::endl;
		PlayerHand->moveCard(DiscardPile, gamestate);
		centerCard = gamestate;
	}
	else if (gamestate->getRank() == Card::Rank::Eight) {
		Rank = true;
		Face = true;
		switchFace(gamestate);
		PlayerHand->moveCard(DiscardPile, gamestate);
	}
	else if (!Rank || !Face) {
		std::cout << "***YOU DREW A CARD***" << std::endl;
		std::cout << std::endl;
		Deck->moveCard(PlayerHand, drawCard);
	}
}


int crazyEights::menu() {
	int choice;
	std::cout << "\nCrazy Eight Menu" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Help" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cout << "Pick from menu: ";
	std::cin >> choice;
	return choice;
}

bool crazyEights::endGame() {
	if (ComputerHand->isEmpty() && PlayerHand->isEmpty() && Deck->isEmpty())
		return true;
	else
		return false;
}

void crazyEights::winGame() {
	if (ComputerHand->isEmpty()) {
		std::cout << " ***COMPUTER WINS*** " << std::endl;
		std::cout << std::endl;
		return;
	}
	if (PlayerHand->isEmpty()) {
		std::cout << " *** YOU WIN, YAY!*** " << std::endl;
		std::cout << std::endl;
		return;
	}
	if (Deck->isEmpty()) {
		std::cout << " ***THE DECK IS EMPTY, BY ELROND TERMS IT IS A TIE***\n";
		std::cout << std::endl;
		return;
	}
}

void crazyEights::playGame() {
	int crazysMenu = menu();

	switch (crazysMenu) {
	case 1: {
		Card* randCard = Deck->getAt(rand() % (Deck->getSize()) + 0);
		Deck->moveCard(DiscardPile, randCard);
		while (!endGame()) {
			playTurn();
			computerTurn();
			saveGame();
			winGame();
		}
		break;
	}
	case 2:
		loadGame();
		while (!endGame()) {
			playTurn();
			computerTurn();
			winGame();
		}
		break;
	case 3:
		helperFunc();
		break;
	case 4:
		exit(0);
	default:
		std::cout << "Invalid option. Try again. \n";
	}
}

void crazyEights::switchFace(Card* c) {
	int choice;
	std::cout << "1: hearts" << std::endl;
	std::cout << "2: diamonds" << std::endl;
	std::cout << "3: spade" << std::endl;
	std::cout << "4: club" << std::endl;
	std::cout << std::endl;
	std::cout << "You played an 8; you get to switch the face: ";
	std::cin >> choice;
	std::cout << std::endl;
	c->setRank(Card::Eight);
	switch (choice) {
	case 1:
		c->setFace(Card::RedHeart);
		std::cout << "Card is now: RedHeart " << c->getRank();
		std::cout << std::endl;
		break;
	case 2:
		c->setFace(Card::RedDiamond);
		std::cout << "Card is now: RedDiamond " << c->getRank();
		std::cout << std::endl;
		break;
	case 3:
		c->setFace(Card::BlackSpade);
		std::cout << "Card is now: BlackSpade " << c->getRank();
		std::cout << std::endl;
		break;
	case 4:
		c->setFace(Card::BlackClub);
		std::cout << "Card is now: BlackClub " << c->getRank();
		std::cout << std::endl;
		break;
	}
	std::cout << std::endl;
}

void crazyEights::computerTurn() {
	Card* gamestate;
	Card* drawCard = Deck->getAt(rand() % (Deck->getSize()) + 0);
	Card* centerCard = DiscardPile->getAt(DiscardPile->getSize() - 1);

	if (hasMove(ComputerHand)) {
		for (int i = 0; i < ComputerHand->getSize(); i++) {
			gamestate = ComputerHand->getAt(i);
			bool Rank = checkRank(gamestate, centerCard);
			bool Face = checkFace(gamestate, centerCard);
			if (Rank) {
				ComputerHand->moveCard(DiscardPile, gamestate);
				std::cout << "***Computer Played Card***" << std::endl;
				std::cout << std::endl;
				centerCard = gamestate;
			}
			else if (Face) {
				ComputerHand->moveCard(DiscardPile, gamestate);
				std::cout << "***Computer Played Card***" << std::endl;
				std::cout << std::endl;
				centerCard = gamestate;
			}
			else if (gamestate->getRank() == Card::Eight) {
				Rank = true;
				Face = true;
				switchCompFace(gamestate);
				ComputerHand->moveCard(DiscardPile, gamestate);
			}
		}
	}
	else {
		Deck->moveCard(ComputerHand, drawCard);
		std::cout << "***Computer Drew Card***" << std::endl;
		std::cout << std::endl;
	}
}

void crazyEights::switchCompFace(Card* c) {
	int randNum = rand() % 4 + 1;
	std::cout << "You played an 8; you get to switch the face" << std::endl;
	std::cout << "1: hearts" << std::endl;
	std::cout << "2: diamonds" << std::endl;
	std::cout << "3: spade" << std::endl;
	std::cout << "4: club" << std::endl;
	std::cout << std::endl;
	c->setRank(Card::Eight);
	switch (randNum) {
	case 1:
		c->setFace(Card::RedHeart);
		std::cout << "Card is now: RedHeart " << c->getRank();
		std::cout << std::endl;
		break;
	case 2:
		c->setFace(Card::RedDiamond);
		std::cout << "Card is now: RedDiamond " << c->getRank();
		std::cout << std::endl;
		break;
	case 3:
		c->setFace(Card::BlackSpade);
		std::cout << "Card is now: BlackSpade " << c->getRank();
		std::cout << std::endl;
		break;
	case 4:
		c->setFace(Card::BlackClub);
		std::cout << "Card is now: BlackClub " << c->getRank();
		std::cout << std::endl;
		break;
	}
	std::cout << std::endl;
}

bool crazyEights::checkFace(Card* play, Card* center) {
	if (play->getFace() == center->getFace())
		return true;
	return false;
}

bool crazyEights::checkRank(Card* play, Card* center) {
	if (play->getRank() == center->getRank())
		return true;
	return false;
}

bool crazyEights::hasMove(cardCollection* c) {
	for (int i = 0; i < c->getSize(); i++)
		if (c->getAtCard(i).getRank() ==
			DiscardPile->getAt(DiscardPile->getSize() - 1)->getRank()
			|| c->getAtCard(i).getFace() ==
			DiscardPile->getAt(DiscardPile->getSize() - 1)->getFace())
			return true;
	return false;
}

void crazyEights::helperFunc() {
	char ans;
	std::cout << "\n***These are the rules for Elrond's crazy 8. Menu*** \n"
		<< "1. The game ends as a tie if drawpile is empty \n"
		<< "2. 8 is a switching card \n"
		<< "3. Can only play one at a time \n"
		<< "Do you what to play the game now(Y/N): ";
	std::cin >> ans;
	switch (ans) {
	case 'Y':
	case 'y':
		playGame();
		break;
	case 'N':
	case 'n':
		std::cout << "\nLeaving Program.";
		break;
	}
}
