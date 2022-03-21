#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Card{
  std::string name;
  std::string type;
  int cost;
public:
  virtual ~Card() = default;
  virtual std::string getName()=0;
  virtual std::string getType()=0;
  virtual std::string getDescription();
  bool isMinion();
  bool isSpell();
  bool isEnchantment();
  bool isRitual();
  virtual void printCard();
  virtual int getCost();
};




#endif
