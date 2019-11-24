/**
* @author Blake McLachlin
* @date Dec 5, 2018
*/

#include "Game.h"
#include "Uno.h"
#include "gtest/gtest.h"
#include "Exceptions.h"

TEST(testUno, endGame) {
    Game* gPtr = new Uno();
    EXPECT_FALSE(gPtr->endGame());
}
