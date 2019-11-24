/**
* @author Blake McLachlin
* @date November 4, 2018
*/

#include "card.h"
#include "drawPile.h"
#include "playerHand.h"
#include "discardPile.h"
#include "gtest/gtest.h"
#include "Exceptions.h"
#include <fstream>

TEST(testDrawPile, outputStream) {
  drawPile dp1(1);
  drawPile dp2(3);
  std::ofstream osTest;
  osTest.open("osTest.txt");
  osTest << dp1 << "\n";
  osTest << dp2 << "\n";
  osTest.close();
}

TEST(testDrawPile, moveCard) {
  drawPile dp(1);
  cardCollection* p1 = new playerHand();
  Card* toPass = new Card(Card::Rank(2), Card::Face(5));
  std::ofstream osTest;
  osTest.open("moveCard.txt");
  osTest << dp;
  osTest << "now moving a Two:RedHeart to the users hand...\n";
  dp.moveCard(p1, toPass);
  osTest << (*p1);
  osTest.close();
}

TEST(testDrawPile, deal) {
  drawPile dp1(1);
  drawPile dp2(3);
  cardCollection* p1 = new playerHand();
  cardCollection* p2 = new playerHand();
  cardCollection* p3 = new playerHand();
  cardCollection* p4 = new playerHand();
  std::ofstream osTest;
  osTest.open("deal.txt");
  osTest << dp1 << "\n";
  osTest << dp2 << "\n";
  dp1.deal(p1, p2);
  dp2.deal(p3, p4);
  osTest << (*p1) << "\n";
  osTest << (*p2) << "\n";
  osTest << (*p3) << "\n";
  osTest << (*p4) << "\n";
  osTest.close();
}

TEST(testDrawPile, getSize) {
    cardCollection* d1 = new drawPile(1);
    cardCollection* d2 = new drawPile(3);
    cardCollection* p1 = new playerHand();
    cardCollection* p2 = new playerHand();
    EXPECT_EQ(52, d1->getSize());
    EXPECT_EQ(108, d2->getSize());
    d1->deal(p1, p2);
    d2->deal(p1, p2);
    EXPECT_EQ(38, d1->getSize());
    EXPECT_EQ(94, d2->getSize());
}

TEST(testDrawPile, insertCard) {
    cardCollection* d1 = new drawPile(1);
    std::ofstream osTest;
    osTest.open("insertCard.txt");
    osTest << *d1 << "\n";
    Card* c = new Card(Card::Rank(2), Card::Face(8));
    d1->insertCard(c);
    osTest << *d1 << "\n";
}
