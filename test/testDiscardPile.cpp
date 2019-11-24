/**
* @author Blake McLachlin
* @date November 4, 2018
*/

#include "discardPile.h"
#include "drawPile.h"
#include "gtest/gtest.h"
#include "Exceptions.h"
#include <fstream>

TEST(testDiscardPile, outputStream) {
  discardPile d1;
  Card* c1 = new Card();
  d1.insertCard(c1);
  d1.show();
}
