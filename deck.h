#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <chrono>
#include "minion.h"
#include "enchantments.h"
#include "spells.h"
#include "ritual.h"

class Deck{
  std::vector<std::unique_ptr<Card>> cards;    
public:
  Deck(std::vector<std::string> decklist);
  std::unique_ptr<Card> draw();
  void randomize();
  bool notEmpty();
  //only for testing, not very nice looking
  void printDeck();
};


#endif
