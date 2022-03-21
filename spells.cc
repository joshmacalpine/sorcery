#include "spells.h"

Spell::Spell(int cost):
  cost(cost)
{}

std::string Spell::getName(){
  return "default name";
}

std::string Spell::getType(){
  return "spell";
}

std::string Spell::getDescription(){
  return "test descript";
}

int Spell::getCost(){
  return cost;
}

std::string Banish::getDescription(){return "Destroy target minion or ritual";}
std::string Unsummon::getDescription(){return "Return target minion to its owner's hand";}
std::string Recharge::getDescription(){return "Your ritual gains 3 charges";}
std::string Disenchant::getDescription(){return "Destroy the top enchantment on target minion";}
std::string RaiseDead::getDescription(){return "Resurrect the top minion in your graveyard and set its defence to 1";}
std::string Blizzard::getDescription(){return "Deal 2 damage to all minions";}


std::string Banish::getName(){return "Banish";}
std::string Unsummon::getName(){return "Unsummon";}
std::string Recharge::getName(){return "Recharge";}
std::string Disenchant::getName(){return "Disenchant";}
std::string RaiseDead::getName(){return "Raise Dead";}
std::string Blizzard::getName(){return "Blizzard";}


Banish::Banish()
  :  Spell{2}
{}

Unsummon::Unsummon()
  : Spell{1}
{}

Recharge::Recharge()
  : Spell{1}
{}

Disenchant::Disenchant()
  : Spell{1}
{}

RaiseDead::RaiseDead()
  : Spell{1}
{}

Blizzard::Blizzard()
  : Spell{3}
{}


