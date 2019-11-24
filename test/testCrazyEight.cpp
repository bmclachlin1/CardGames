/**
* @author Prosper Ibhamawu
* @date December 5, 2018
*/

#include "crazyEights.h"
#include "gtest/gtest.h"

TEST(testCrazyEights, checkingFaceTest) {
  Card* c1 = new Card(Card::Ace, Card::BlackSpade);
  Card* c2 = new Card(Card::Ace, Card::BlackClub);
  Card* c3 = new Card(Card::Ace, Card::BlackSpade);

  crazyEights crazy;
  EXPECT_FALSE(crazy.checkFace(c1, c2));
  EXPECT_TRUE(crazy.checkFace(c1, c3));
}

TEST(testCrazyEights, checkingRankTest) {
  Card* c1 = new Card(Card::Ace, Card::BlackSpade);
  Card* c2 = new Card(Card::Two, Card::BlackClub);
  Card* c3 = new Card(Card::Ace, Card::BlackSpade);

  crazyEights crazy;
  EXPECT_FALSE(crazy.checkRank(c1, c2));
  EXPECT_TRUE(crazy.checkRank(c1, c3));
}

TEST(testCrazyEights, winGameTest) {
  crazyEights c1;
  Card* card1 = new Card();
  Card* card2 = new Card();
  for (int i = 0; i < 52; i++) {
    c1.getDeck()->moveCard(c1.getDiscardPile(),
                           c1.getDeck()->getAt(0));
  }
  c1.winGame();
  c1.getComputerHand()->insertCard(card1);
  c1.winGame();
  c1.getPlayerHand()->insertCard(card2);
  c1.winGame();
}


TEST(testCrazyEights, compSwitchFacetest) {
  crazyEights c1;
  Card* c = new Card();
  c1.switchCompFace(c);
}
