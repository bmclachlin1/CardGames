/**
* @author Blake McLachlin
* @date November 4, 2018
*/

#include "card.h"
#include "cardCollection.h"
#include "playerHand.h"
#include "drawPile.h"
#include "gtest/gtest.h"
#include "Exceptions.h"
#include <fstream>

TEST(testplayerHand, outputStream) {
    cardCollection* p1 = new playerHand();
    cardCollection* p2 = new playerHand();
    cardCollection* d1 = new drawPile(1);

    std::ofstream osTest;
    osTest.open("osTest2.txt");
    osTest << "The deck contains:\n";
    osTest << (*d1);
    d1->deal(p1, p2);
    osTest << "Your hand contains:\n";
    osTest << (*p1);
    osTest << "Computer's hand contains:\n";
    osTest << (*p2);
    osTest.close();
}

TEST(testPlayerHand, isEmptyTest) {
  cardCollection* p1 = new playerHand();
  Card* c1 = new Card();

  EXPECT_TRUE(p1->isEmpty());
  p1->insertCard(c1);
  EXPECT_FALSE(p1->isEmpty());
}

TEST(testPlayerHand, getAtTest) {
  cardCollection* p1 = new playerHand();
  Card* c1 = new Card();

  p1->insertCard(c1);

  EXPECT_TRUE((*c1) == (*p1->getAt(0)));
}

TEST(testPlayerHand, getRankAt) {
  cardCollection* p1 = new playerHand();
  Card* c1 = new Card();

  p1->insertCard(c1);
}

TEST(testPlayerHand, containsRankTest) {
  cardCollection* p1 = new playerHand();
  Card* c1 = new Card();
  Card* c2 = new Card();

  p1->insertCard(c1);

  EXPECT_TRUE(p1->containsRank(c2));
}

TEST(testPlayerHand, getSizeTest) {
  cardCollection* p1 = new playerHand();
  Card* c1 = new Card();

  EXPECT_EQ(0, p1->getSize());
  p1->insertCard(c1);
  EXPECT_EQ(1, p1->getSize());
}
