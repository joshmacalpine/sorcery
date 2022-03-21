#include "card.h"


std::string Card::getDescription(){
  return "";
}

bool Card::isMinion(){
  return getType()=="minion";
}

bool Card::isSpell(){
  return getType()=="spell";
}

bool Card::isEnchantment(){
  return getType()=="enchantment";
}

bool Card::isRitual(){
  return getType()=="ritual";
}

void Card::printCard(){
  std::cout<<getName()<<std::endl;
}

int Card::getCost(){
  std::cerr<<"Very bad, should not be here"<<std::endl;
  return 0;
}
