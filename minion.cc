#include "minion.h"

Minion::Minion(int attack,int defence,int summonCost,int abilityCost, bool activatedAbility,bool triggeredAbility)
  :defaultAttack{attack},
   defaultDefence{defaultDefence},
   attack{attack},
   defence{defence},
   summonCost{summonCost},
   abilityCost{abilityCost},
   actionPoints{0},
   canUseAbilities{1},
   activatedAbility{activatedAbility},
   triggeredAbility{triggeredAbility}
{}

int Minion::getCost(){
  return summonCost;
}

bool Minion::dead(){
  return defence<=0;
}

std::string Minion::getType(){
    return "minion";
}

std::string Minion::getName(){
  return "default name";
}

Minion::~Minion(){
  enchants.clear();
}
bool Minion::isAlive(){
  return defence>0;
}

void Minion::damage(Minion *other){
  defence-=other->attack;
}

void Minion::setActionPoints(int i){
  actionPoints = i;
}
void Minion::changeActionPoints(int delta){
  actionPoints=std::max(0,actionPoints+delta);
}
void Minion::enableAbilities(){
  canUseAbilities = 1;
}
void Minion::disableAbilities(){
  canUseAbilities = 0;
}
bool Minion::canAbil(){
  return canUseAbilities;
}
const bool Minion::hasActivatedAbility(){
  return activatedAbility;
}

const bool Minion::hasTriggeredAbility(){
  return triggeredAbility;
}

bool Minion::apLeft(){
  return actionPoints>0;
}

const int Minion::getAttack(){
  return attack;
}

const int Minion::getDefence(){
  return defence;
}

const int Minion::getSummonCost(){
  return summonCost;
}

const int Minion::getAbilityCost(){
  return abilityCost;
}

void Minion::changeAttack(int i){
  attack+=i;
}

void Minion::setDefence(int i){
  defence = i;
}
void Minion::setAttack(int i){
  attack = i;
}

void Minion::changeDefence(int i){
  defence+=i;
}
void Minion::changeAbilityCost(int i){
  abilityCost+=i;
}
void Minion::addEnchantment(Enchantment* e){
  enchants.emplace_back(nullptr);
  enchants[enchants.size()-1] = e;
}

void Minion::eraseEnchantment(Player* ap, Player* nap){
  enchants.back()->destructAbility(this,ap,nap);
  enchants.pop_back();
}

bool Minion::hasEnchant(){
  return enchants.size()>0;
}
int Minion::numEnchantments(){
  return enchants.size();
}

Enchantment* Minion::getEnchantment(int i){
  if(i<numEnchantments()){
    return (Enchantment*)(enchants[i]);
  }else{
    return nullptr;
  }
}



std::string BlueEyesWhiteDragon::getDescription(){return "???";}
std::string AirElemental::getDescription(){return "???";}
std::string EarthElemental::getDescription(){return "???";}
std::string Bomb::getDescription(){return "Deals damage to all the opponent minions equal to its attack value when it dies";}
std::string FireElemental::getDescription(){return "Whenever an opponent's minion enters play, deal 1 damage to it";}
std::string PotionSeller::getDescription(){return "At the end of your turn, all your minions gain +0/+1";}
std::string NovicePyromancer::getDescription(){return "Deal 1 damage to target minion";}
std::string ApprenticeSummoner::getDescription(){return "Summon a 1/1 air elemental";}
std::string MasterSummoner::getDescription(){return "Summon up to three 1/1 air elementals";}


std::string BlueEyesWhiteDragon::getName(){return "Blue Eyes White Dragon";}
std::string AirElemental::getName(){return "Air Elemental";}
std::string EarthElemental::getName(){return "Earth Elemental";}
std::string Bomb::getName(){return "Bomb";}
std::string FireElemental::getName(){return "Fire Elemental";}
std::string PotionSeller::getName(){return "Potion Seller";}
std::string NovicePyromancer::getName(){return "Novice Pyromancer";}
std::string ApprenticeSummoner::getName(){return "Apprentice Summoner";}
std::string MasterSummoner::getName(){return "Master Summoner";}



BlueEyesWhiteDragon::BlueEyesWhiteDragon()
  :  Minion{3000,2500,0,0,0,0}
{}

AirElemental::AirElemental()
  : Minion{1,1,0,0,0,0}
{}


EarthElemental::EarthElemental()
  : Minion{4,4,3,0,0,0}
{}

Bomb::Bomb()
  : Minion{1,2,2,0,0,1}
{}

FireElemental::FireElemental()
  : Minion{2,2,2,0,0,1}
{}

PotionSeller::PotionSeller()
  : Minion{1,3,2,0,0,1}
{}

NovicePyromancer::NovicePyromancer()
  : Minion{0,1,1,1,1,0}
{}

ApprenticeSummoner::ApprenticeSummoner()
  : Minion{1,1,1,1,1,0}
{}

MasterSummoner::MasterSummoner()
  : Minion{2,3,3,2,1,0}
{}

Exodia::Exodia()
  : Minion{5,5,3,0,1,0}
{}
std::string Exodia::getName(){return "Exodia";}
std::string Exodia::getDescription(){return "When all five pieces of Exodia are gathered, win the game";}

LeftLeg::LeftLeg()
  : Minion{2,2,1,0,0,0}
{}
std::string LeftLeg::getName(){return "Left Leg";}

RightLeg::RightLeg()
  : Minion{2,2,1,0,0,0}
{}
std::string RightLeg::getName(){return "Right Leg";}

LeftArm::LeftArm()
  : Minion{2,2,1,0,0,0}
{}
std::string LeftArm::getName(){return "Left Arm";}

RightArm::RightArm()
  : Minion{2,2,1,0,0,0}
{}
std::string RightArm::getName(){return "Right Arm";}

CatapultTurtle::CatapultTurtle()
  : Minion(0,6,2,1,1,0)
{}
std::string CatapultTurtle::getName(){return "Catapult Turtle";}
std::string CatapultTurtle::getDescription(){return "Sacrife one monster on your side of the field to damage your opponent";}

GiantSoldier::GiantSoldier()
  : Minion{0,10,2,0,0,0}
{}
std::string GiantSoldier::getName(){return "Giant Soldier";}

SummonedSkull::SummonedSkull()
  : Minion{6,6,4,0,0,0}
{}
std::string SummonedSkull::getName(){return "Summoned Skull";}

CelticGuardian::CelticGuardian()
  : Minion{3,2,2,0,0,0}
{}
std::string CelticGuardian::getName(){return "Celtic Guardian";}

Obelisk::Obelisk()
  : Minion{40,40,5,0,1,0}
{}
std::string Obelisk::getName(){return "Obelisk the Tormentor";}
std::string Obelisk::getDescription(){return "Destroy all other monsters on the field";}
Slifer::Slifer()
  : Minion{1,1,5,0,0,1}
{}
std::string Slifer::getName(){return "Slifer the Sky Dragon";}
std::string Slifer::getDescription(){return "Has a power level equivalent to cards in your hand at summon time x10";}
Ra::Ra()
  : Minion{1,1,5,0,0,1}
{}
std::string Ra::getName(){return "The Sun Dragon Ra";}
std::string Ra::getDescription(){return "??????????????????????";}
DarkMagician::DarkMagician()
  : Minion{8,5,3,0,1,0}
{}
std::string DarkMagician::getName(){return "Dark Magician";}
std::string DarkMagician::getDescription(){return "Gains one additional attack per turn";}
WaterGuardian::WaterGuardian()
  : Minion{2,5,3,0,0,0}
{}
std::string WaterGuardian::getName(){return "Water Guardian";}
WindGuardian::WindGuardian()
  : Minion{5,2,3,0,0,0}
{}
std::string WindGuardian::getName(){return "Wind Guardian";}
ThunderGuardian::ThunderGuardian()
  : Minion{4,4,3,0,1,0}
{}
std::string ThunderGuardian::getName(){return "Thunder Guardian";}
std::string ThunderGuardian::getDescription(){return "Can summon a powerful monster when all three guardians are gathered";}

GateGuardian::GateGuardian()
  : Minion{25,25,0,0,0,0}
{}
std::string GateGuardian::getName(){return "Gate Guardian";}

