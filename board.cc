#include "board.h"
#include "ascii_graphics.h"

Minion* makeMinion(Card* m){
  return (Minion*) m;
}

Enchantment* makeEnchant(Card* e){
  return (Enchantment*) e;
}

Ritual* makeRitual(Card* r){
  return (Ritual*) r;
}


bool Board::validMinion(unsigned int i){
  return i<minions.size();
}

bool Board::hasRitual(){
  return ritual.size()>0;
}

bool Board::canPlay(Card* c){
  std::string s = c->getType();

  if(s=="minion"){
    return minions.size()<5;
  }else if(s=="ritual"){
    return ritual.size()==0;
  }
  return 0;
}

void Board::play(std::unique_ptr<Card> m){
  std::string s = m->getType();
  
  if(s=="minion"){
    minions.emplace_back(std::move(m));
  }else if(s=="enchantment"){
    enchantments.emplace_back(std::move(m));
  }else if(s=="ritual"){
    ritual.emplace_back(std::move(m));;
  }


}



Minion* Board::getMinion(unsigned int i){
  if(i<minions.size()){
    return ((Minion*)minions[i].get());
  }
  return nullptr;
}

Ritual* Board::getRitual(){
  if(hasRitual()){
    return ((Ritual*)ritual[0].get());
  }
  return nullptr;
}

void Board::defendAgainst(int i, Card* attacker){
  if(validMinion(i)){
    getMinion(i)->damage(makeMinion(attacker));
  }else{
    std::cerr<<"Something went wrong"<<std::endl;
  }
}

void Board::damageAll(int i){
  for(unsigned int j = 0;j<minions.size();j++){
    getMinion(j)->changeDefence(-i);
  }
}


std::vector<std::unique_ptr<Card>> Board::getDead(Player* ap,Player* nap){
  std::vector<std::unique_ptr<Card>> bringOutYourDead;
  for(unsigned int i = 0;i<minions.size();){
    if(makeMinion(minions[i].get())->dead()){
      Minion* m = getMinion(i);
      if(m->canAbil()){
	m->destructAbility(ap,nap);
      }else{
	m->defaultDestruct(ap,nap);
      }
      bringOutYourDead.emplace_back(std::move(minions[i]));
      minions.erase(minions.begin()+i);
    }else{
      i++;
    }
  }
  for(unsigned int i = enchantments.size();i>0;i--){
    if(makeEnchant(enchantments[i-1].get())->getParent()==nullptr){
      std::cout<<enchantments[i-1]->getName()<<" is being discarded like trash"<<std::endl;
      // bringOutYourDead.emplace_back(std::move(enchantments[i]));
      enchantments.pop_back();
    }else{
    }
  }

  if(hasRitual()&&getRitual()->getCharges()<=0){
    getRitual()->destructAbility(ap,nap);
    ritual.clear();
  }
  
  return bringOutYourDead;
}

int Board::numMinions(){
  return minions.size();
}

void Board::addMinion(std::unique_ptr<Card> m){
  minions.emplace_back(std::move(m));
}


void Board::beginTurn(Player* ap, Player* nap){
  for(unsigned int i = 0;i<minions.size();i++){
    Minion* m = getMinion(i);
    m->setActionPoints(1);
    if(m->canAbil()){
      m->beginAbility(ap,nap);
    }
  }
  if(hasRitual()){
    getRitual()->beginAbility(ap,nap);
  }
}

void Board::eot(Player* ap, Player* nap){
  for(unsigned int i = 0;i<minions.size();i++){
    Minion* m = getMinion(i);
    if(m->canAbil()){
      m->eotAbility(ap,nap);
    }
  }
  if(hasRitual()){
    getRitual()->eotAbility(ap,nap);
  }
}

void Board::enterPlay(Card* card,Player* ap,Player* nap,bool selfEnter){
  for(unsigned int i = 0;i<minions.size();i++){
    Minion* m = getMinion(i);
    if(m->canAbil()){
      m->enterAbility(makeMinion(card),ap,nap,selfEnter);
    }
  }
  if(hasRitual()){
    getRitual()->enterAbility(makeMinion(card),ap,nap,selfEnter);
  }
}

std::unique_ptr<Card> Board::takeCard(int i){
  std::unique_ptr<Card> temp = std::move(minions[i]);
  minions.erase(minions.begin()+i);
  return std::move(temp);
}

void Board::removeRitual(){
  ritual.clear();
}

void Board::setSelf(Player* s){
  owner = s;
}

void Board::setOther(Player* o){
  other = o;
}

void Board::inspector(int i) {
  Minion* mip = getMinion(i);
  if(mip == nullptr) {
    std::cout << "Minion does not exist on your side of the board" << std::endl;;
    return;
  }
  
  const int card_dimensions = 11;
  // draw the minion
  
  card_template_t pcard;
	
  if(mip->hasTriggeredAbility() == true) {
    pcard = display_minion_triggered_ability(mip->getName(),mip->getCost(), mip->getAttack(), 
					     mip->getDefence(), mip->getDescription());
  }else if(mip->hasActivatedAbility() == true) {
    pcard = display_minion_activated_ability(mip->getName(),mip->getCost(), mip->getAttack(), 
					     mip->getDefence(), mip->getAbilityCost(), mip->getDescription());
    
  } else {
    pcard = display_minion_no_ability(mip->getName(),mip->getCost(),mip->getAttack(),mip->getDefence());
	}
  
  
  
	for(int i = 0; i < card_dimensions; i++) {
	  std::cout<<pcard[i]<<std::endl;;
	}
	
	
	//draw the enchantments, 5 per line
	
	if(mip->hasEnchant() == false) {
	  return;
	}
	
	std::vector<card_template_t> enchantlist;
	
	for(int i = 0; i < mip->numEnchantments(); i++) {
	  card_template_t ecard;
	  
	  if(mip->getEnchantment(i)->getAttack() == "" || mip->getEnchantment(i)->getDefence() == "") {
	    
	    ecard = display_enchantment(mip->getEnchantment(i)->getName(), mip->getEnchantment(i)->getCost(), mip->getEnchantment(i)->getDescription());
	  } else {
	    
	    ecard = display_enchantment_attack_defence(mip->getEnchantment(i)->getName(), mip->getEnchantment(i)->getCost(), mip->getEnchantment(i)->getDescription(),
						       mip->getEnchantment(i)->getAttack(), mip->getEnchantment(i)->getDefence());
	  }
	  
	  enchantlist.emplace_back(ecard);
	}
	
	int elenlist = enchantlist.size();
	int ecount = 0;
	while(elenlist > 0) {
	  for(int i = 0; i < card_dimensions; i++) {
	    std::string printer;
	    if(elenlist >= 5) {
	      for(int j = 0; j < 5; j++) {
		printer = printer + enchantlist[j+ecount][i];
	      }	
	      std::cout<<printer<<std::endl;;
	    } else {
	      for(int j = 0; j < elenlist; j++) {
		printer = printer + enchantlist[j+ecount][i];
	      }
	      std::cout<<printer<<std::endl;;
	    }
	  }
	  elenlist = elenlist - 5;
	  ecount = ecount + 5;
	  std::cout<<std::endl;;
	}
}

bool Board::hasCard(std::string c){
  for(unsigned int i = 0;i<minions.size();i++){
    if(minions[i]->getName()==c){
      return true;
    }
  }
  return false;
}
