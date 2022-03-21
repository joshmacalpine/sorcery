#ifndef _HAND_H_
#define _HAND_H_



#include <vector>
#include <memory>
#include <iostream>
#include "card.h"



class Hand{
  std::vector<std::unique_ptr<Card>> hand;
public:
  void addCard(std::unique_ptr<Card> newCard);
  void discard(unsigned int idx);
  void printCard(unsigned int idx);
  void printHand();
  Card* ithCard(unsigned int i);
  std::unique_ptr<Card> takeCard(int i);
  int getSize();  
};


#endif
