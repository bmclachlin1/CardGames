/**
* @author Prosper Ibhamawu
* @date 01/November/2018
*/

#include <iostream>
#include <iomanip>
#include "drawPile.h"
#include "playerHand.h"
#include "discardPile.h"
#include "cardCollection.h"
#include "card.h"
#include "Game.h"
#include "goFish.h"
#include "crazyEights.h"
#include "Uno.h"
#include <cstring>


const int GO_FISH = 1;
const int CRAZY_8 = 2;
const int UNO = 3;

void mainMenu();

int main() {

	mainMenu();

	return 0;
}

void mainMenu() {
	int choice;
	do {
		std::cout << std::setfill('*') << std::setw(85);
		std::cout << "\nWelcome to Project Elrond's Card Simulator" << std::endl;
		std::cout << "Main Menu" << std::endl;
		std::cout << "1. Go Fish" << std::endl;
		std::cout << "2. Crazy Eights" << std::endl;
		std::cout << "3. Uno" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cin >> choice;
	} while (choice < 1 || choice > 4);

	if (choice == 1) {
		Game* gPtr = new goFish();
		gPtr->playGame();
	}

	else if (choice == 2) {
		Game* gPtr = new crazyEights();
		gPtr->playGame();
	}

	else if (choice == 3) {
		Game* gPtr = new Uno();
		gPtr->playGame();
	}
	else if (choice == 4)
		std::cout << "Closing program\n";
}

