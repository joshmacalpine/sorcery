#include "ritual.h"

Ritual::Ritual(int summonCost,int activationCost,int charges):
  summonCost{summonCost},
  activationCost{activationCost},
  charges{charges}
{}

int Ritual::getCost(){
  return summonCost;
}

std::string Ritual::getType(){
  return "ritual";
}

std::string Ritual::getName(){
  return "default ritual name";
}

const int Ritual::getActivationCost(){
  return activationCost;
}

const int Ritual::getCharges(){
  return charges;
}

void Ritual::changeCharges(int changeBy){
  charges+=changeBy;
}

void Ritual::activation(){
  charges-=activationCost;
}
void Ritual::setCharges(int i){
  charges = i;
}

std::string DarkRitual::getDescription(){return "At the start of your turn, gain 1 magic";}
std::string AuraofPower::getDescription(){return "Whenever a minion enters play under your control, it gains +1/+1";}
std::string Standstill::getDescription(){return "Whenever a minion enters play, destroy it";}

std::string DarkRitual::getName(){return "Dark Ritual";}
std::string AuraofPower::getName(){return "Aura of Power";}
std::string Standstill::getName(){return "Standstill";}



DarkRitual::DarkRitual()
  : Ritual{0,1,5}
{}

AuraofPower::AuraofPower()
  : Ritual{1,1,4}
{}

Standstill::Standstill()
  : Ritual{3,2,4}
{}
