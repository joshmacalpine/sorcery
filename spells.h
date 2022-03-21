#ifndef _SPELLS_H_
#define _SPELLS_H_

#include <string>
#include "card.h"

class Player;

class Spell : public Card{
  const int cost;
public:
  Spell(int cost);
  std::string getName() override;
  std::string getDescription();
  std::string getType() override;
  int getCost() override;
  virtual bool tryPlay(int,int,Player*,Player*);
};

class Banish : public Spell{
public:
  Banish();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};

class Unsummon : public Spell{
public:
  Unsummon();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};

class Recharge : public Spell{
public:
  Recharge();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};

class Disenchant : public Spell{
public:
  Disenchant();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};

class RaiseDead : public Spell{
public:
  RaiseDead();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};

class Blizzard : public Spell{
public:
  Blizzard();
  std::string getName() override;
  std::string getDescription() override;
  bool tryPlay(int,int,Player*,Player*) override;
};



#endif
