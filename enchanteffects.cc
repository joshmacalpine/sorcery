#include "player.h"


void Enchantment::printCard(){
  if(parent!=nullptr){
    std::cout<<getName()<<" parent: " << parent->getName()<<std::endl;
  }else{
    std::cout<<getName()<<std::endl;
  }
}

void Enchantment::summonAbility(Minion* m, Player* ap, Player* nap){
  setParent(m);
}

void Enchantment::destructAbility(Minion* m, Player* ap, Player* nap){
  setParent(nullptr);
}

void Enchantment::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  
}

void Enchantment::beginAbility(Player* ap, Player* nap){
}

void Enchantment::eotAbility(Player* ap, Player* nap){
}

void GiantStrength::summonAbility(Minion* m, Player* ap, Player* nap){
  setParent(m);
  m->changeAttack(2);
  m->changeDefence(2);
}

void GiantStrength::destructAbility(Minion* m, Player* ap, Player* nap){
  setParent(nullptr);
  m->changeAttack(-2);
  m->changeDefence(-2);
}

void Enrage::summonAbility(Minion* m, Player* ap, Player* nap){
  setParent(m);
  m->changeAttack(m->getAttack());
  m->changeDefence(-2);
}

void Enrage::destructAbility(Minion* m, Player* ap, Player* nap){
  setParent(nullptr);
  m->changeAttack(-m->getAttack()/2);
  m->changeDefence(2);
}

void Delay::beginAbility(Player* ap,Player* nap){
  getParent()->setActionPoints(0);
}

void MagicFatigue::summonAbility(Minion* m, Player* ap, Player* nap){  
  setParent(m);
  m->changeAbilityCost(2);
}

void MagicFatigue::destructAbility(Minion* m, Player* ap, Player* nap){
  setParent(nullptr);
  m->changeAbilityCost(-2);
}

void Silence::summonAbility(Minion* m, Player* ap, Player* nap){
  setParent(m);
  m->disableAbilities();
}

void Silence::destructAbility(Minion* m, Player* ap, Player* nap){
  setParent(nullptr);
  m->enableAbilities();
}
