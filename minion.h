#ifndef _MINION_H_
#define _MINION_H_

#include <string>
#include <vector>
#include "card.h"
#include "enchantments.h"

class Player;

class Minion : public Card{
  const int defaultAttack;
  const int defaultDefence;
  int attack;
  int defence;
  const int summonCost;
  int abilityCost;
  int actionPoints;
  bool canUseAbilities;
  bool activatedAbility;
  bool triggeredAbility;
  std::vector<Enchantment*> enchants;
public:
  virtual ~Minion() override;
  Minion(int attack, int defence,int summonCost,int abilityCost,bool activatedAbility,bool triggeredAbility);
  std::string getType() override;
  std::string getName() override;
  int getCost() override;
  bool isAlive();
  bool dead();
  void damage(Minion*);
  void doneForTurn();
  void setActionPoints(int);
  void changeActionPoints(int);
  const int getAttack();
  const int getDefence();
  const int getSummonCost();
  const int getAbilityCost();
  void setAttack(int);
  void setDefence(int);
  void changeAttack(int i);
  void changeDefence(int i);
  void changeAbilityCost(int i);
  bool canAbil();
  bool apLeft();
  const bool hasActivatedAbility();
  const bool hasTriggeredAbility();
  void enableAbilities();
  void disableAbilities();
  virtual bool activateAbility(int,int,int,Player*,Player*);
  virtual void eotAbility(Player*,Player*);
  virtual void destructAbility(Player*,Player*);
  virtual void enterAbility(Minion*, Player*,Player*,bool);
  virtual void beginAbility(Player*,Player*);
  
  void defaultEOT(Player*,Player*);
  void defaultDestruct(Player*,Player*);
  void defaultEnter(Minion*, Player*,Player*,bool);
  void defaultBegin(Player*,Player*);
  bool hasEnchant();
  void addEnchantment(Enchantment*);
  void eraseEnchantment(Player*,Player*);
  int numEnchantments();
  Enchantment* getEnchantment(int);
};






class AirElemental : public Minion{
public:
  AirElemental();
  std::string getName() override;
  std::string getDescription() override;
};

class EarthElemental : public Minion{
public:
  EarthElemental();
  std::string getName() override;
  std::string getDescription() override;
};

class Bomb : public Minion{
public:
  Bomb();
  std::string getName() override;
  void destructAbility(Player*,Player*) override;
  std::string getDescription() override;
};

class FireElemental : public Minion{
public:
  FireElemental();
  std::string getName() override;
  void enterAbility(Minion*,Player*,Player*,bool) override;
  std::string getDescription() override;
};

class PotionSeller : public Minion{
public:
  PotionSeller();
  std::string getName() override;
  void eotAbility(Player*,Player*) override;
  std::string getDescription() override;
};

class NovicePyromancer : public Minion{
public:
  NovicePyromancer();
  std::string getName() override;
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getDescription() override;
};

class ApprenticeSummoner : public Minion{
public:
  ApprenticeSummoner();
  std::string getName() override;
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getDescription() override;

};

class MasterSummoner : public Minion{
public:
  MasterSummoner();
  std::string getName() override;
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getDescription() override;
};



//Bonus Cards

class BlueEyesWhiteDragon : public Minion{

public:
  BlueEyesWhiteDragon();
  std::string getName() override;
  std::string getDescription() override;
};


class Exodia : public Minion{
public:
  Exodia();
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getName() override;
  std::string getDescription() override;
};
class LeftLeg : public Minion{
public:
  LeftLeg();
  std::string getName() override;
};
class RightLeg : public Minion{
public:
  RightLeg();
  std::string getName() override;
};
class LeftArm : public Minion{
public:
  LeftArm();
  std::string getName() override;
};
class RightArm : public Minion{
public:
  RightArm();
  std::string getName() override;
};
class CatapultTurtle : public Minion{
public:
  CatapultTurtle();
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getName() override;
  std::string getDescription() override;
};
class GiantSoldier : public Minion{
public:
  GiantSoldier();
  std::string getName() override;
};
class SummonedSkull : public Minion{
public:
  SummonedSkull();
  std::string getName() override;
};

class CelticGuardian : public Minion{
public:
  CelticGuardian();
  std::string getName() override;  
};

class Obelisk : public Minion{
public:
  Obelisk();
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getName() override;
  std::string getDescription() override;
};

class Slifer : public Minion{
public:
  Slifer();
  void enterAbility(Minion*,Player*,Player*,bool) override;
  std::string getName() override;
  std::string getDescription() override;
};

class Ra : public Minion{
public:
  Ra();
  void enterAbility(Minion*,Player*,Player*,bool) override;
  std::string getName() override;
  std::string getDescription() override;
};
class DarkMagician : public Minion{
public:
  DarkMagician();
  std::string getName() override;
  void beginAbility(Player*,Player*) override;
  std::string getDescription() override;
};
class WaterGuardian : public Minion{
public:
  WaterGuardian();
  std::string getName() override;
};
class WindGuardian : public Minion{
public:
  WindGuardian();
  std::string getName() override;  
};

class ThunderGuardian : public Minion{
public:
  ThunderGuardian();
  bool activateAbility(int,int,int,Player*,Player*) override;
  std::string getName() override;
  std::string getDescription() override;
};

class GateGuardian : public Minion{
public:
  GateGuardian();
  std::string getName() override;
};


#endif
