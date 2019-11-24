/**
* @author Cassady Campos
* @date October 31, 2018
*/

#include "playerHand.h"
#include <iostream>

playerHand::playerHand() {
	this->sizeOf = 0;
}

void playerHand::show() {
	for (int i = 0; i < sizeOf; i++)
		std::cout << i << ". " << *(deck[i]) << std::endl;
}
