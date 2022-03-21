#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include <memory>
#include "deck.h"
#include "hand.h"
#include "board.h"
#include "graveyard.h"
#include "minion.h"

class Player{
  Board board;
  Deck deck;
  Hand hand;
  Graveyard graveyard;
  int health = 25;
  int magic = 3;
  std::string name;
  bool testing;
public: 
  Player(std::string name,std::vector<std::string> decklist,bool testing);
  const int getMagic();
  const int getHealth();
  void printDeck();
  void printHand();
  void draw();
  void discard(int);
  void play(unsigned int i,Player*);
  void play(std::unique_ptr<Card>,Player*);
  void printBoard(int playerNum);
  void play(int i, int p, int t, Player* ap, Player* nap);
  void use(int i,int p, int t,Player* aP,Player* nAP);
  std::string getName();
  void toGY(std::unique_ptr<Card>);
  void shuffle();
  void changeMagic(int i);
  void changeHealth(int i);
  bool hasMinion(unsigned int idx);
  bool defenceless();
  Minion* getMinion(int idx);
  Ritual* getRitual();
  void defendAgainst(int i, Card* attacker);
  void defend(Card* attacker);
  void resolve(Player*,Player*);
  void printGraveyard();
  int numMinions();
  void addMinion(std::unique_ptr<Card>);
  void beginTurn(Player*,Player*);
  void damageAll(int);
  void eot(Player*,Player*);
  void toHand(std::unique_ptr<Card> c);
  std::unique_ptr<Card> minionFromBoard(int i);
  std::unique_ptr<Card> getFirstDead();
  int handSize();
  bool nonEmptyGraveyard();
  bool canAttack(int);
  bool isDead();
  Card* gdead();
  void setOppon(Player*);
  void describe(int);
  bool hasCard(std::string);
};

#endif
