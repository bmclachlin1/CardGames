/**
* @author Blake McLachlin
* @date October 31, 2018
*/

#include "./cardCollection.h"
#include <vector>
#include <fstream>
#include <iostream>


cardCollection::cardCollection() {}

cardCollection::~cardCollection() {
	for (unsigned int i = 0; i < deck.size(); i++) {
		delete deck[i];
		deck[i] = nullptr;
	}
}

void cardCollection::moveCard(cardCollection* receiver, Card* c) {
	for (int i = 0; i < this->sizeOf; i++) {
		bool flag = true;
		if (receiver == nullptr || c == nullptr) {
			flag = false;
			std::cerr << "some throw message \n";
		}
		if ((*c) == *(deck[i]) && flag == true) {
			deck.erase(deck.begin() + i);
			receiver->deck.push_back(c);
			this->sizeOf--;
			receiver->sizeOf++;
			break;
		}
	}
}

void cardCollection::insertCard(Card* c) {
	bool flag = true;
	if (c == nullptr) {
		std::cerr << "some throw message \n";
		flag = false;
	}
	if (flag == true) {
		this->deck.push_back(c);
		this->sizeOf++;
	}
}

bool cardCollection::isEmpty() {
	return deck.empty();
}

Card* cardCollection::getAt(int i) {
	return deck[i];
}
Card cardCollection::getAtCard(int i) {
	return *(deck[i]);
}
Card* cardCollection::getRankAt(Card* c) {
	for (int i = 0; i < sizeOf; i++)
		if (deck[i]->getRank() == (*c).getRank())
			return deck[i];
	return nullptr;
}

bool cardCollection::containsRank(Card* c) {
	for (int i = 0; i < sizeOf; i++) {
		if (deck[i]->getRank() == (*c).getRank())
			return true;
	}
	return false;
}
std::ostream& operator<<(std::ostream& os, cardCollection& c) {
	for (int i = 0; i < c.sizeOf; i++) {
		os << i << ": " << *(c.deck[i]) << std::endl;
	}
	return os;
}

int cardCollection::getSize() const {
	return sizeOf;
}


