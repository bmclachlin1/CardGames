/**
* @author Cassady Campos
* @date December 5, 2018
*/

#include "goFish.h"
#include "gtest/gtest.h"

TEST(testgoFish, endGameTest) {
  Game* g1 = new goFish();

  for (int i = 0; i < 52; i++) {
    g1->getDeck()->moveCard(g1->getDiscardPile(),
                            g1->getDeck()->getAt(0));
  }
  EXPECT_TRUE(g1->getDeck()->isEmpty());
  EXPECT_TRUE(g1->endGame());
}

TEST(testgoFish, getPlayerScoreTest) {
  goFish g1;

  EXPECT_EQ(0, g1.getPlayerScore());
}

TEST(testgoFish, getComputerScoreTest) {
  goFish g1;

  EXPECT_EQ(0, g1.getComputerScore());

  g1.declareWinner();
}

TEST(testgoFish, checkForSetTest) {
  goFish game1;

  Card* ace1 = new Card(Card::Rank::Ace, Card::Face::RedHeart);
  Card* ace2 = new Card(Card::Rank::Ace, Card::Face::RedDiamond);
  Card* ace3 = new Card(Card::Rank::Ace, Card::Face::BlackSpade);
  Card* ace4 = new Card(Card::Rank::Ace, Card::Face::BlackClub);

  game1.getPlayerHand()->insertCard(ace1);
  game1.getPlayerHand()->insertCard(ace2);
  game1.getPlayerHand()->insertCard(ace3);
  game1.getPlayerHand()->insertCard(ace4);

  EXPECT_EQ(0, game1.getPlayerScore());

  game1.checkForSet();

  EXPECT_EQ(1, game1.getPlayerScore());
}

TEST(testgoFish, checkComputerTest) {
  goFish game1;

  Card* King1 = new Card(Card::Rank::King, Card::Face::RedHeart);
  Card* King2 = new Card(Card::Rank::King, Card::Face::RedDiamond);
  Card* King3 = new Card(Card::Rank::King, Card::Face::BlackSpade);
  Card* King4 = new Card(Card::Rank::King, Card::Face::BlackClub);

  game1.getComputerHand()->insertCard(King1);
  game1.getComputerHand()->insertCard(King2);
  game1.getComputerHand()->insertCard(King3);
  game1.getComputerHand()->insertCard(King4);

  EXPECT_EQ(0, game1.getComputerScore());

  game1.checkComputer();

  EXPECT_EQ(1, game1.getComputerScore());
}
