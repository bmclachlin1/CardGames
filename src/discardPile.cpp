/**
* @author Blake McLachlin
* @date November 6, 2018
*/

#include "discardPile.h"
#include <iostream>

discardPile::discardPile() {
	this->sizeOf = 0;
}

void discardPile::show() {
	std::cout << *(this->deck[sizeOf - 1]) << "\n";
}
