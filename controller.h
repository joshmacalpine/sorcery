#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <fstream>
#include "player.h"


class Controller{
  std::unique_ptr<Player> Player1;
  std::unique_ptr<Player> Player2;
  Player* activePlayer;
  Player* nonActivePlayer;
  bool testing;
public:
  Controller(std::string p1, std::string p2,std::vector<std::string> deck1list,std::vector<std::string> deck2list,bool testing);
  void init();
  void switchPlayers();
  std::string whosTurn();
  void printActiveDeck();
  void draw(int);
  void discard(int i);
  void attack(int i);
  void attack(int i, int j);
  void play(int i);
  void play(int i, int p, int target);
  //If p==0, then it is just a simple not targeted use
  void use(int i, int p, int target);
  void describe(int i);
  void displayHand();
  void displayBoard();
  void shuffle(int n);
  void defendAgainst(int i, Minion* attacker);
  void printGraveyard();
  bool gameOver();
  void setPlayers();
};

#endif
