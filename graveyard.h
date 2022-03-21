#ifndef _GRAVEYARD_H_
#define _GRAVEYARD_H_



#include <vector>
#include <memory>
#include <iostream>
#include "card.h"



class Graveyard{
  std::vector<std::unique_ptr<Card>> graveyard;
public:
  void addCard(std::unique_ptr<Card> newCard);
  void printCard(unsigned int idx);
  void printGraveyard();
  bool notEmpty();
  std::unique_ptr<Card> graverob();
  Card* gcard();
};


#endif
