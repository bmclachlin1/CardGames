/**
* @author Cassady Campos
* @date November 6 2018
*/

#include "Game.h"

cardCollection* Game::getDeck() {
	return Deck;
}

cardCollection* Game::getPlayerHand() {
	return PlayerHand;
}

cardCollection* Game::getComputerHand() {
	return ComputerHand;
}

cardCollection* Game::getDiscardPile() {
	return DiscardPile;
}
