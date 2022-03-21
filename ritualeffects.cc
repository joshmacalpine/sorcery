#include "player.h"

void Ritual::eotAbility(Player* ap, Player* nap){
  
}

void Ritual::destructAbility(Player* ap, Player* nap){
  
}

void Ritual::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  
}

void Ritual::beginAbility(Player* ap, Player* nap){
  
}


void DarkRitual::beginAbility(Player* ap, Player* nap){
  ap->changeMagic(1);
  activation();
}

void AuraofPower::enterAbility(Minion* m, Player* ap, Player* nap, bool selfEnter){
  if(selfEnter){
    m->changeAttack(1);
    m->changeDefence(1);
    activation();
  }
}


void Standstill::enterAbility(Minion* m, Player* ap, Player* nap, bool selfEnter){
  m->setDefence(0);
  activation();
}
