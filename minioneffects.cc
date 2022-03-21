#include "player.h"

void Minion::defaultEOT(Player* ap, Player* nap){
  for(unsigned int i = 0;i<enchants.size();i++){
    enchants[enchants.size()-i-1]->eotAbility(ap,nap);
  }
}

void Minion::defaultDestruct(Player* ap, Player* nap){
  for(unsigned int i = 0;i<enchants.size();i++){
    enchants[enchants.size()-i-1]->destructAbility(this,ap,nap);
  }
  enchants.clear();
  setActionPoints(0);
}

void Minion::defaultEnter(Minion* m,Player* ap, Player* nap,bool selfEnter){
  for(unsigned int i = 0;i<enchants.size();i++){
    enchants[enchants.size()-i-1]->enterAbility(m,ap,nap,selfEnter);
  }
}


void Minion::defaultBegin(Player* ap, Player* nap){
  for(unsigned int i = 0;i<enchants.size();i++){
    enchants[enchants.size()-i-1]->beginAbility(ap,nap);
  }
}



bool Minion::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  std::cerr<<aP->getMinion(i)->getName()<<" does not have an activated ability"<<std::endl;
  return 0;
}

void Minion::eotAbility(Player* ap, Player* nap){
  defaultEOT(ap,nap);
}

void Minion::destructAbility(Player* ap, Player* nap){
  defaultDestruct(ap,nap);
}

void Minion::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  defaultEnter(m,ap,nap,selfEnter);
}

void Minion::beginAbility(Player* ap, Player* nap){
  defaultBegin(ap,nap);
}

bool NovicePyromancer::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  if(canAbil()){
    if(p==1){
      ((Minion*)aP->getMinion(t))->changeDefence(-1);
      aP->resolve(aP,nAP);
      return 1;
    }else if(p==2){
      ((Minion*)nAP->getMinion(t))->changeDefence(-1);
      nAP->resolve(nAP,aP);
      return 1;
    }else{
      std::cerr<<"Novice Pyromancers ability must name a target"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}

bool ApprenticeSummoner::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  if(canAbil()){
    if(p==0){
      if((5-aP->numMinions())>0){
	aP->play(std::move(std::make_unique<AirElemental>(AirElemental{})),nAP);
	return 1;
      }else{
	std::cerr<<"No room to summon an Air Elemental"<<std::endl;
	return 0;
      }
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}

bool MasterSummoner::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  if(canAbil()){
    if(p==0){
      int n = std::min(3,5-aP->numMinions());
      if(n==0){
	std::cerr<<"No room to summon an Air Elemental"<<std::endl;
	return 0;
    }
      while(n>0){
	n--;
	aP->play(std::move(std::make_unique<AirElemental>(AirElemental{})),nAP);
      }
      return 1;
    }else{
      std::cerr<<"Invalid target for Master Summoner's ability"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}

void Bomb::destructAbility(Player* ap, Player* nap){
  if(canAbil()){
  nap->damageAll(getAttack());
  //  nap->resolve(nap,ap);
  }
  defaultDestruct(ap,nap);
}


//Maybe pass along index of monster
void FireElemental::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  if(canAbil()){
  if(selfEnter){
  }else{
    m->changeDefence(-1);
    std::cout<<getName()<< " damaged your "<< m->getName()<<std::endl;
  }
  }
  defaultEnter(m,ap,nap,selfEnter);
}

void PotionSeller::eotAbility(Player* ap, Player* nap){
  if(canAbil()){
    ap->damageAll(-1);
  }
  defaultEOT(ap,nap);
}




//Unique Abilities


bool CatapultTurtle::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  if(canAbil()){
    if(p==1){
      Minion* m = aP->getMinion(t);
      if(m==nullptr){
	std::cerr<<"Can't sacrife something that doesn't exist"<<std::endl;
	return 0;
      }else{
	nAP->changeHealth(-m->getAttack());
	m->setDefence(0);
	aP->resolve(aP,nAP);
	return 1;
      }
    }else{
      std::cerr<<getName()<<" must target one of your own monsters"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}


bool Exodia::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  if(canAbil()){
    if(p==0){
      if(aP->hasCard("Left Leg")&&aP->hasCard("Left Arm")&&aP->hasCard("Right Leg")&&aP->hasCard("Right Arm")){
	std::cout<<"Exodia, Obliterate"<<std::endl;
	//The damage, its OVER 9000!!!!!!1
	nAP->changeHealth(-9000);
	return 1;
      }
    }else{
      std::cerr<<getName()<<" must not name a target"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Missing Pieces of Exodia"<<std::endl;
  return 0;
}

bool Obelisk::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  Minion* m;
  if(canAbil()){
    if(p==0){
      std::cout<<"Obelisk! God Hand Crusher!"<<std::endl;
      for(int i = 0;i<aP->numMinions();i++){
	m = aP->getMinion(i);
	if(m!=this&&m!=nullptr){
	  m->setDefence(0);
	}
      }
      for(int i = 0;i<nAP->numMinions();i++){
	m=nAP->getMinion(i);
	if(m!=nullptr){
	  m->setDefence(0);
	}
      }
      nAP->resolve(nAP,aP);
      aP->resolve(aP,nAP);
      return 1;
    }else{
      std::cerr<<getName()<<" must not name a target"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}

void Slifer::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  if(canAbil()){
    if(m==this){
      m->setAttack(ap->handSize()*10);
      m->setDefence(ap->handSize()*10);
    }
  }
  defaultEnter(m,ap,nap,selfEnter);
}

void Ra::enterAbility(Minion* m,Player* ap, Player* nap,bool selfEnter){
  int total = 0;
  Minion* n;
  if(canAbil()&&m==this){
    for(int i = 0;i<ap->numMinions();i++){
	 n = ap->getMinion(i);
	 if(n!=this&&n!=nullptr){
	   total+=n->getAttack();
	   n->setDefence(0);
	 }
       }
       
       m->setAttack(total*10);
    m->setDefence(total*10);
  }
  defaultEnter(m,ap,nap,selfEnter);
}



void DarkMagician::beginAbility(Player* ap, Player* nap){
  defaultBegin(ap,nap);
  if(canAbil()){
    this->changeActionPoints(1);
  }
}

bool ThunderGuardian::activateAbility(int i, int p, int t, Player* aP,Player* nAP){
  int waterGuardianPos = 6;
  int windGuardianPos = 6;
  if(canAbil()){
    if(p==0){
      for(int i = aP->numMinions();i>0;i--){
	if(aP->getMinion(i)!=nullptr&&aP->getMinion(i)->getName()=="Water Guardian"){
	  waterGuardianPos = i;
	}else if(aP->getMinion(i)!=nullptr&&aP->getMinion(i)->getName()=="Wind Guardian"){
	  windGuardianPos = i;
	}
      }
      if(waterGuardianPos==6||windGuardianPos==6){
	std::cerr <<"All the guardians are not gathered on the field"<<std::endl;
	return 0;
      }else{
	aP->getMinion(waterGuardianPos)->setDefence(0);
	aP->getMinion(windGuardianPos)->setDefence(0);
	this->setDefence(0);
	aP->resolve(aP,nAP);	  
	aP->play(std::make_unique<GateGuardian>(GateGuardian{}),nAP);
	return 1;
      }
    }else{
      std::cerr<<getName()<<" must not name a target"<<std::endl;
      return 0;
    }
  }
  std::cerr<<"Failed to activate ability"<<std::endl;
  return 0;
}
