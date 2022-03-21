#ifndef _RITUAL_H_
#define _RITUAL_H_

#include <string>
#include "card.h"

class Player;
class Minion;

class Ritual : public Card{
  const int summonCost;
  const int activationCost;
  int charges;
public:
  Ritual(int summonCost,int activationCost,int charges);
  std::string getType() override;
  std::string getName() override;
  int getCost() override;
  const int getActivationCost();
  const int getCharges();
  void changeCharges(int);
  void setCharges(int);
  void activation();
  virtual void eotAbility(Player*,Player*);
  virtual void enterAbility(Minion*,Player*,Player*,bool);
  virtual void beginAbility(Player*,Player*);
  virtual void destructAbility(Player*,Player*);
};


class DarkRitual : public Ritual{
public:
  DarkRitual();
  std::string getName() override;
  std::string getDescription() override;
  void beginAbility(Player*,Player*) override;
};

class AuraofPower : public Ritual{
public:
  AuraofPower();
  std::string getName() override;
  std::string getDescription() override;
  void enterAbility(Minion*,Player*,Player*,bool) override;
};

class Standstill : public Ritual{
public:
  Standstill();
  std::string getName() override;
  std::string getDescription() override;
  void enterAbility(Minion*,Player*,Player*,bool) override;
};


#endif
