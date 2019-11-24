/**
* @author Cassady Campos
* @date October 31 2018
*/

#include "card.h"
#include "gtest/gtest.h"
#include "Exceptions.h"

TEST(testCard, getRankTest) {
  Card card1;
  Card card2(static_cast<Card::Rank>(5), static_cast<Card::Face>(6) );

  EXPECT_EQ(Card::Ace, card1.getRank());
  EXPECT_EQ(Card::Five, card2.getRank());

  card1.setRank(Card::King);
  EXPECT_EQ(Card::King, card1.getRank());
}

TEST(testCard, getFaceTest) {
  Card card1;
  Card card2(static_cast<Card::Rank>(5), static_cast<Card::Face>(6) );

  EXPECT_EQ(Card::BlackSpade, card1.getFace());
  EXPECT_EQ(Card::RedDiamond, card2.getFace());

  card1.setFace(Card::RedDiamond);
  EXPECT_EQ(Card::RedDiamond, card1.getFace());
}

TEST(testCard, ostreamTest) {
  Card card1;
  Card card2(Card::Two, Card::RedDiamond);
  std::stringstream s1, s2, s3;
    s1 << card1;
    s2 << card1;
    s3 << card2;

  EXPECT_EQ(s1.str(), s2.str());
  EXPECT_NE(s1.str(), s3.str());
}

TEST(testCard, equalsOperatorTest) {
  Card card1;
  Card card2;
  Card card3(Card::Rank::King, Card::Face::RedHeart);

  EXPECT_TRUE(card1 == card2);
  card2.setRank(Card::Rank::Queen);
  EXPECT_FALSE(card1 == card2);

  EXPECT_FALSE(card1 == card3);
}

TEST(testCard, printCardTest) {
  Card card1;

  card1.printCard(std::cout);
}

TEST(testCard, assignmentOperatorTest) {
  Card card1;

  Card card2(Card::Rank::Eight, Card::Face::BlackClub);
  EXPECT_FALSE(card1 == card2);
  card2 = card1;

  EXPECT_TRUE(card1 == card2);
}
