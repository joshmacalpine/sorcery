#include "enchantments.h"



Enchantment::Enchantment(int summonCost,std::string attackChange="",std::string defenceChange=""):
  summonCost{summonCost},
  attackChange{attackChange},
  defenceChange{defenceChange},
  parent{nullptr}
{}


std::string Enchantment::getType(){
  return "enchantment";
}

std::string Enchantment::getName(){
  return "default ename";
}

int Enchantment::getCost(){
  return summonCost;
}

void Enchantment::setParent(Minion* m){
  parent = m;
}
Minion* Enchantment::getParent(){
  return parent;
}
std::string Enchantment::getAttack(){
  return attackChange;
}
std::string Enchantment::getDefence(){
  return defenceChange;
}



std::string GiantStrength::getDescription(){return "";}
std::string GiantStrength::getName(){return "Giant Strength";}

std::string Enrage::getDescription(){return "";}
std::string Enrage::getName(){return "Enrage";}

std::string Delay::getDescription(){return "Enchanted minion does not gain an action on their next turn. This enchantment is automatically destroyed after 1 turn";}
std::string Delay::getName(){return "Delay";}

std::string MagicFatigue::getDescription(){return "Enchanted minion's activated ability costs 2 more";}
std::string MagicFatigue::getName(){return "Magic Fatigue";}

std::string Silence::getDescription(){return "Enchanted minion cannot use abilities";}
std::string Silence::getName(){return "Silence";}

GiantStrength::GiantStrength()
  : Enchantment{1,"+2","+2"}
{}

Enrage::Enrage()
  : Enchantment{2,"*2","-2"}
{}

Delay::Delay()
  : Enchantment{1}
{}

MagicFatigue::MagicFatigue()
  : Enchantment{0}
{}

Silence::Silence()
  : Enchantment{1}
{}
