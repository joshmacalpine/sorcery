#include "player.h"

const int Player::getMagic(){
  return magic;
}

const int Player::getHealth(){
  return health;
}

void Player::printDeck(){
  deck.printDeck();
}

void Player::changeHealth(int i){
  health+=i;
  if(health<0){
    health = 0;
  }
}
void Player::changeMagic(int i){
  magic+=i;
  if(magic<0){
    magic = 0;
  }
}


Player::Player(std::string name,std::vector<std::string> decklist,bool testing):
  deck{Deck{decklist}},
  name{name},
  testing{testing}
{}

std::string Player::getName(){
  return name;
}

void Player::printHand(){
  hand.printHand();
}

void Player::printGraveyard(){
  graveyard.printGraveyard();
}

void Player::draw(){
  if(deck.notEmpty() && hand.getSize()<5){
    hand.addCard(deck.draw());
  }
}
void Player::discard(int i){
  hand.discard(i);
}

void Player::shuffle(){
  deck.randomize();
}

void Player::play(unsigned int i,Player* other){
  Card* c = hand.ithCard(i);
  if(c==nullptr){
    std::cerr<<"No card exists at that index"<<std::endl;
  }else if(c->isEnchantment()){
    std::cerr<<"An enchantment must name a target"<<std::endl;
  }else if(c->isSpell()){
    Spell* s = (Spell*)c;
    if(magic>=s->getCost()||testing){
    if(s->tryPlay(0,0,this,other)){
      std::cout<<"Playing "<< s->getName()<<std::endl;
      magic = std::max(magic-s->getCost(),0);
      resolve(this,other);
      resolve(other,this);
      //toGY(std::move(hand.takeCard(i))
      hand.takeCard(i);
    }else{
      std::cerr<<"Cannot play spell "<<c->getName()<<std::endl;
    }
    } else{
      std::cerr<<"The cost is to great"<<std::endl;
    }
  }else if(c->isRitual()){
    if(c->getCost()<=magic||testing){
      magic = std::max(magic-c->getCost(),0);
      board.removeRitual();
      std::cout<<"Playing "<<c->getName()<<std::endl;
      board.play(std::move(hand.takeCard(i)));
    }else{
      std::cerr<<"The cost is to great"<<std::endl;
    }
  }else if(board.canPlay(c)){
    if(c->getCost()<=magic||testing){
      magic=std::max(magic-c->getCost(),0);
      std::cout<<"Playing "<<c->getName()<<std::endl;
      board.play(std::move(hand.takeCard(i)));
      board.enterPlay(c,this,other,1);
      resolve(this,other);
      other->board.enterPlay(c,other,this,0);
      resolve(other,this);
    }else{
      std::cerr<<"The cost is to great"<<std::endl;
    }
  }else{
    std::cerr<<"No room on board to play "<<c->getName()<<std::endl;
  }
}

void Player::play(std::unique_ptr<Card> m,Player* other){
  Card* c = m.get();
  std::cout<<"Summoning "<<c->getName()<<std::endl;
  board.play(std::move(m));
  board.enterPlay(c,this,other,1);
  resolve(this,other);
  other->board.enterPlay(c,other,this,0);
  resolve(other,this);
}

void Player::play(int i, int p, int t, Player* ap, Player* nap){
  Card* c = hand.ithCard(i);
  if(c==nullptr){
    std::cerr<<"No card exists at that index"<<std::endl;
  }else if(!testing&&c->isSpell()&&c->getCost()>magic){
    std::cerr<<"The cost is too great"<<std::endl;
  }else if(c->isMinion()){
    std::cerr<<"Summoning a minion cannot name a target"<<std::endl;
  }else if(c->isRitual()){
    std::cerr<<"Playing a ritual cannot name a target"<<std::endl;
  }else if(c->isEnchantment()){
    Enchantment* e = (Enchantment*) c;
    Minion* m = nullptr;
    if(p==1){
      m = ap->getMinion(t);
    }else if(p==2){
      m = nap->getMinion(t);
    }
    if(m==nullptr){
      std::cerr<<"No minion exists at that index to play an enchantment on"<<std::endl;
      return;
    }else if(c->getCost()>magic&&!testing){
      std::cerr<<"The cost is too great"<<std::endl;
    }else{
      std::cout<<"Playing " <<c->getName()<<std::endl;
      magic=std::max(magic-c->getCost(),0);
      m->addEnchantment(e);
      e->summonAbility(m, ap, nap);
      board.play(hand.takeCard(i));
    }
  }else if(c->isSpell()){
    Spell* s = (Spell*)c;
    if(s->tryPlay(p,t,ap,nap)){
      std::cout<<"Playing "<<s->getName()<<std::endl;
      magic=std::max(magic-c->getCost(),0);
      toGY(std::move(hand.takeCard(i)));
    }else{
      std::cerr<<"Invalid play of spell "<<c->getName()<<std::endl;
    }
  }else{
    std::cerr<<"Then what is it?"<<std::endl;
  }
  resolve(ap,nap);
  resolve(nap,ap);
}


void Player::printBoard(int playerNum){
  board.print(playerNum);
}


Minion* Player::getMinion(int idx){
  return board.getMinion(idx);
}


bool Player::defenceless(){
  return !hasMinion(0);
}

bool Player::hasMinion(unsigned int idx){
  return board.validMinion(idx);
}

void Player::defendAgainst(int i, Card* attacker){
  board.defendAgainst(i, attacker);
}

void Player::defend(Card* attacker){
  health -= ((Minion*)attacker)->getAttack();
}

void Player::resolve(Player* ap, Player* nap){
  std::vector<std::unique_ptr<Card>> dead = board.getDead(ap,nap);
  bool redo = dead.size()>0;
  
  while(dead.size()>0){
    if(dead.back()->isMinion()){
      toGY(std::move(dead[dead.size()-1]));
    }
    dead.pop_back();
  }
  
  if(redo){
    ap->resolve(ap,nap);
    nap->resolve(nap,ap);
  }
}
void Player::use(int i, int p, int t, Player* aP, Player* nAP){
  //defilter t, 5 now means ritual
  t-=1;
  if(!aP->hasMinion(i)){
    std::cerr<<"You don't have a minion at that index"<<std::endl;
  }else if(t==5&&p==1&&!aP->board.hasRitual()){
    std::cerr<<"You don't have a ritual"<<std::endl;
  }else if(t==5&&p==2&&!nAP->board.hasRitual()){
    std::cerr<<nAP->getName()<<" doesn't have a ritual"<<std::endl;
  }else if(p==1&&!aP->hasMinion(t)){
    std::cerr<<"You don't have a minion at target index"<<std::endl;
  }else if(p==2&&!nAP->hasMinion(t)){
    std::cerr<<nAP->getName()<<" doesn't have a minion at target index"<<std::endl;
  }else{
    Minion* m = board.getMinion(i);
    if(m->canAbil()&&m->hasActivatedAbility()){
      if((m->apLeft()&&m->getAbilityCost()<=magic)||testing){
	if(m->activateAbility(i,p,t,aP,nAP)){
	  magic=std::max(0,magic-m->getAbilityCost());
	  m->changeActionPoints(-1);
	}
      }else{
	std::cerr<<"The cost is to great, for a weak minion like "<< m->getName()<<std::endl;
      }
    }else{
      std::cerr<<m->getName()<<" cannot activate their ability"<<std::endl;
    }
  }
}

int Player::numMinions(){
  return board.numMinions();
}

void Player::addMinion(std::unique_ptr<Card> m){
  board.addMinion(std::move(m));
}

void Player::beginTurn(Player* ap, Player* nap){
  draw();
  magic++;
  board.beginTurn(ap,nap);
  resolve(ap,nap);
  resolve(nap,ap);
}

void Player::damageAll(int i){
  board.damageAll(i);
}

void Player::toGY(std::unique_ptr<Card> c){
  if(c->isMinion()){
      graveyard.addCard(std::move(c));
    }
}

void Player::eot(Player* ap, Player* nap){
  board.eot(ap,nap);
  resolve(ap,nap);
  resolve(nap,ap);
}

Ritual* Player::getRitual(){
  return board.getRitual();
}


void Player::toHand(std::unique_ptr<Card> c){
  hand.addCard(std::move(c));
}

std::unique_ptr<Card> Player::minionFromBoard(int i){
  return std::move(board.takeCard(i));;
}

int Player::handSize(){
  return hand.getSize();
}

std::unique_ptr<Card> Player::getFirstDead(){
  return std::move(graveyard.graverob());
}

bool Player::nonEmptyGraveyard(){
  return graveyard.notEmpty();
}

bool Player::canAttack(int i){
  Minion* m = getMinion(i);
  if(m == nullptr){
    std::cerr<<"Not good"<<std::endl;
    return 0;
  }else if (m->apLeft()){
    m->changeActionPoints(-1);
    return 1;
  }
  std::cerr<<m->getName()<<" is out of action points"<<std::endl;
  return 0;
}
bool Player::isDead(){
  return health<=0;
}

Card* Player::gdead(){
  return graveyard.gcard();
}
void Player::setOppon(Player* other){
  board.setSelf(this);
  board.setOther(other);
}
void Player::describe(int i){
  board.inspector(i);
}
bool Player::hasCard(std::string c){
  return board.hasCard(c);
}
