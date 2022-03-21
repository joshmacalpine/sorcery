#ifndef _ENCHANT_H_
#define _ENCHANT_H_

#include <string>
#include "card.h"

class Player;
class Minion;

class Enchantment : public Card{
  int summonCost;
  std::string attackChange;
  std::string defenceChange;
  Minion* parent;
public:
  Enchantment(int summonCost,std::string attackChange,std::string defenceChange);
  Minion* getParent();
  std::string getType() override;
  std::string getName() override;
  std::string getAttack();
  std::string getDefence();
  int getCost() override;
  void setParent(Minion*);
  virtual void summonAbility(Minion*,Player*,Player*);
  virtual void destructAbility(Minion*,Player*,Player*);
  virtual void enterAbility(Minion*,Player*,Player*,bool);
  virtual void beginAbility(Player*,Player*);
  virtual void eotAbility(Player*,Player*);
  void printCard() override;
};


class GiantStrength : public Enchantment{
public:
  GiantStrength();
  std::string getName() override;
  std::string getDescription() override;
  void summonAbility(Minion*,Player*,Player*) override;
  void destructAbility(Minion*,Player*,Player*) override;
};

class Enrage : public Enchantment{
public:
  Enrage();  
  std::string getName() override;
  std::string getDescription() override;
  void summonAbility(Minion*,Player*,Player*) override;
  void destructAbility(Minion*,Player*,Player*) override;
};

class Delay : public Enchantment{
public:
  Delay();
  std::string getName() override;
  std::string getDescription() override;
  void beginAbility(Player*,Player*) override;
};

class MagicFatigue : public Enchantment{
public:
  MagicFatigue();
  std::string getName() override;
  std::string getDescription() override;
  void summonAbility(Minion*,Player*,Player*) override;
  void destructAbility(Minion*,Player*,Player*) override;
};

class Silence : public Enchantment{
public:
  Silence();
  std::string getName() override;
  std::string getDescription() override;
  void summonAbility(Minion*,Player*,Player*) override;
  void destructAbility(Minion*,Player*,Player*) override;
};

#endif
