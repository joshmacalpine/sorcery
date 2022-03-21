#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "card.h"
#include "minion.h"
#include "enchantments.h"
#include "ritual.h"
#include "spells.h"

class Player;

class Board{
  std::vector<std::unique_ptr<Card>> minions;
  std::vector<std::unique_ptr<Card>> enchantments;
  std::vector<std::unique_ptr<Card>> ritual;
  Player* owner = nullptr;
  Player* other = nullptr;
public:
  void play(std::unique_ptr<Card> m);
  void print(int playerNum);
  bool canPlay(Card*);
  bool hasRitual();
  bool validMinion(unsigned int i);
  Minion* getMinion(unsigned int i);
  Ritual* getRitual();
  void defendAgainst(int i, Card* attacker);
  std::vector<std::unique_ptr<Card>> getDead(Player*,Player*);
  int numMinions();
  void addMinion(std::unique_ptr<Card>);
  void eot(Player*,Player*);
  void beginTurn(Player*,Player*);
  void damageAll(int);
  void addGY(std::unique_ptr<Card>);
  void enterPlay(Card*,Player*,Player*,bool);
  std::unique_ptr<Card> takeCard(int);
  void removeRitual();
  void setSelf(Player*);
  void setOther(Player*);
  void inspector(int);
  bool hasCard(std::string);
};


#endif
