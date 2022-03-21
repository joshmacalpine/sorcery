#include "player.h"

bool Spell::tryPlay(int p, int t, Player* ap, Player* nap){
  std::cerr<<"Default spell effect, should not occur"<<std::endl;
  return 0;
}


bool Banish::tryPlay(int p, int t, Player* ap, Player* nap){
  Minion* m = nullptr;
  Ritual* r = nullptr;
 
  if(p==1){
    r = ap->getRitual();
    m = ap->getMinion(t);
    if(t==5&&(r==nullptr)){
      std::cerr<<"You have no ritual"<<std::endl;
      return 0;
    }else if(t==5){
      r->setCharges(0);
      return 1;
    }else if(m==nullptr){
      std::cerr<<"You have no minion at that index"<<std::endl;
      return 0;
    }else{
      m->defaultDestruct(ap,nap);
      m->setDefence(0);
      return 1;
    }
  }else if(p==2){
    r = nap->getRitual();
    m = nap->getMinion(t);
    if(t==5&&(r==nullptr)){
      std::cerr<<nap->getName()<<" has no ritual"<<std::endl;
      return 0;
    }else if(t==5){
      r->setCharges(0);
      return 1;
    }else if(m==nullptr){
      std::cerr<<nap->getName()<<" has no minion at that index"<<std::endl;
      return 0;
    }else{
      m->defaultDestruct(nap,ap);
      m->setDefence(0);
      return 1;
    }
  }
  return 0;
}

bool Unsummon::tryPlay(int p, int t, Player* ap, Player* nap){
  Minion* m = nullptr;
  if(t==5){
    std::cerr<<"Can't unsummon a ritual"<<std::endl;
  }
  if(p==1){
    m = ap->getMinion(t);
    if(m==nullptr){
      std::cerr<<"You have no minion at that index"<<std::endl;
      return 0;
    }else{
      if(ap->handSize()<5){
	m->defaultDestruct(ap,nap);
	ap->toHand(std::move(ap->minionFromBoard(t)));
	return 1;
      }else{
	std::cerr<<"Your hand is full"<<std::endl;
	return 0;
      }
    }
  }
  else if(p==2){
      m = nap->getMinion(t);
      if(m==nullptr){
	std::cerr<<nap->getName()<<" has no minion at that index"<<std::endl;
      }else{
	if(nap->handSize()<5){
	  m->defaultDestruct(nap,ap);
	  nap->toHand(std::move(nap->minionFromBoard(t)));
	  return 1;
	}else{
	  std::cerr<<nap->getName()<<"'s hand is full"<<std::endl;
	  return 0;
	}
      }
  }
  return 0;
}  

bool Recharge::tryPlay(int p, int t, Player* ap, Player* nap){
  if(p!=0){
    std::cerr<<"Recharge does not take a target"<<std::endl;
    return 0;
  }else{
    Ritual* r = ap->getRitual();
    if(r==nullptr){
      std::cerr<<"You have no ritual"<<std::endl;
    }else{
      r->changeCharges(3);
      return 1;
    }
  }
  return 0;
}

bool Disenchant::tryPlay(int p, int t, Player* ap, Player* nap){
  if(t==5||p==0){
    std::cout<<"Disenchant must target a minion"<<std::endl;
  }
  if(p==1){
    Minion* m = ap->getMinion(t);
    if(m==nullptr){
      std::cerr<<"You have no minion at that index"<<std::endl;
      return 0;
    }else if(!m->hasEnchant()){
      std::cerr<<m->getName()<< " has no enchantments attached"<<std::endl;
      return 0;
    }else{
      m->eraseEnchantment(ap,nap);
      return 1;
    }
  }else if(p==2){
    Minion* m = nap->getMinion(t);
    if(m==nullptr){
      std::cerr<<nap->getName()<<" has no minion at that index"<<std::endl;
      return 0;
    }else if(!m->hasEnchant()){
      std::cerr<<m->getName()<< " has no enchantments attached"<<std::endl;
      return 0;
    }else{
      m->eraseEnchantment(nap,ap);
      return 1;
    }
  }
  return 0;
}

bool RaiseDead::tryPlay(int p, int t, Player* ap, Player* nap){
  if(p!=0){
    std::cerr<<"Raise Dead should not name a target"<<std::endl;
    return 0;
  }
  if(ap->nonEmptyGraveyard()){
    std::unique_ptr<Card> temp = ap->getFirstDead();
    ((Minion*)(temp.get()))->setDefence(1);
    ap->play(std::move(temp),nap);
    return 1;
  }else{
    std::cerr<<"Your graveyard is empty"<<std::endl;
    return 0;
  }
}

bool Blizzard::tryPlay(int p, int t, Player* ap, Player* nap){
  nap->damageAll(2);
  ap->damageAll(2);
  return 1;
}
