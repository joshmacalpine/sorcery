#include "deck.h"

using namespace std;

void Deck::printDeck(){
  for(unsigned int i = 0;i<cards.size();i++){
    cout<<cards[i]->getName()<<endl;
  }
}

unique_ptr<Card> Deck::draw(){
  unique_ptr<Card> temp = std::move(cards.back());
  cards.pop_back();
  return temp;
}

bool Deck::notEmpty(){
  return cards.size()>0;
}

void Deck::randomize(){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng{seed};
  for(int i = 0;i<1000;i++){
    shuffle(cards.begin(),cards.end(),rng);
  }
}

Deck::Deck(vector<string> decklist){
  string blueEyes = "Blue Eyes White Dragon";
  string darkMagician = "Dark Magician";
  string banish = "Banish";
  string unsummon = "Unsummon";
  string recharge = "Recharge";
  string disenchant = "Disenchant";
  string raiseDead = "Raise Dead";
  string blizzard = "Blizzard";
  string airElemental = "Air Elemental";
  string earthElemental = "Earth Elemental";
  string bomb = "Bomb";
  string fireElemental = "Fire Elemental";
  string potionSeller = "Potion Seller";
  string novicePyromancer = "Novice Pyromancer";
  string apprenticeSummoner = "Apprentice Summoner";
  string masterSummoner = "Master Summoner";
  string giantStrength = "Giant Strength";
  string enrage = "Enrage";
  string delay = "Delay";
  string magicFatigue = "Magic Fatigue";
  string silence = "Silence";
  string darkRitual = "Dark Ritual";
  string auraofPower = "Aura of Power";
  string standstill = "Standstill";
  string exodia = "Exodia";
  string rightarm = "Right Arm";
  string leftarm = "Left Arm";
  string rightleg = "Right Leg";
  string leftleg = "Left Leg";
  string catapult = "Catapult Turtle";
  string giant = "Giant Soldier";
  string skull = "Summoned Skull";
  string celtic = "Celtic Guardian";
  string obelisk = "Obelisk the Tormentor";
  string slifer = "Slifer the Sky Dragon";
  string ra = "The Sun Dragon Ra";
  string waterGuard = "Water Guardian";
  string thunderGuard = "Thunder Guardian";
  string windGuard = "Wind Guardian";

  while(decklist.size()>0){
    string c = decklist.back();
    decklist.pop_back();
    if(c==blueEyes){
      cards.emplace_back(make_unique<BlueEyesWhiteDragon>(BlueEyesWhiteDragon{}));
    }else if(c==banish){
      cards.emplace_back(make_unique<Banish>(Banish{}));
    }else if(c==unsummon){
      cards.emplace_back(make_unique<Unsummon>(Unsummon{}));
    }else if(c==recharge){
      cards.emplace_back(make_unique<Recharge>(Recharge{}));
    }else if(c==disenchant){
      cards.emplace_back(make_unique<Disenchant>(Disenchant{}));
    }else if(c==raiseDead){
      cards.emplace_back(make_unique<RaiseDead>(RaiseDead{}));
    }else if(c==blizzard){
      cards.emplace_back(make_unique<Blizzard>(Blizzard{}));
    }else if(c==airElemental){
      cards.emplace_back(make_unique<AirElemental>(AirElemental{}));
    }else if(c==earthElemental){
      cards.emplace_back(make_unique<EarthElemental>(EarthElemental{}));
    }else if(c==bomb){
      cards.emplace_back(make_unique<Bomb>(Bomb{}));
    }else if(c==fireElemental){
      cards.emplace_back(make_unique<FireElemental>(FireElemental{}));
    }else if(c==potionSeller){
      cards.emplace_back(make_unique<PotionSeller>(PotionSeller{}));
    }else if(c==novicePyromancer){
      cards.emplace_back(make_unique<NovicePyromancer>(NovicePyromancer{}));
    }else if(c==apprenticeSummoner){
      cards.emplace_back(make_unique<ApprenticeSummoner>(ApprenticeSummoner{}));
    }else if(c==masterSummoner){
      cards.emplace_back(make_unique<MasterSummoner>(MasterSummoner{}));
    }else if(c==giantStrength){
      cards.emplace_back(make_unique<GiantStrength>(GiantStrength{}));
    }else if(c==enrage){
      cards.emplace_back(make_unique<Enrage>(Enrage{}));
    }else if(c==delay){
      cards.emplace_back(make_unique<Delay>(Delay{}));
    }else if(c==magicFatigue){
      cards.emplace_back(make_unique<MagicFatigue>(MagicFatigue{}));
    }else if(c==silence){
      cards.emplace_back(make_unique<Silence>(Silence{}));
    }else if(c==darkRitual){
      cards.emplace_back(make_unique<DarkRitual>(DarkRitual{}));
    }else if(c==auraofPower){
      cards.emplace_back(make_unique<AuraofPower>(AuraofPower{}));
    }else if(c==standstill){
      cards.emplace_back(make_unique<Standstill>(Standstill{}));
    }else if(c==exodia){
      cards.emplace_back(make_unique<Exodia>(Exodia{}));
    }else if(c==leftarm){
      cards.emplace_back(make_unique<LeftArm>(LeftArm{}));
    }else if(c==rightarm){
      cards.emplace_back(make_unique<RightArm>(RightArm{}));
    }else if(c==leftleg){
      cards.emplace_back(make_unique<LeftLeg>(LeftLeg{}));
    }else if(c==rightleg){
      cards.emplace_back(make_unique<RightLeg>(RightLeg{}));
    }else if(c==catapult){
      cards.emplace_back(make_unique<CatapultTurtle>(CatapultTurtle{}));
    }else if(c==giant){
      cards.emplace_back(make_unique<GiantSoldier>(GiantSoldier{}));
    }else if(c==skull){
      cards.emplace_back(make_unique<SummonedSkull>(SummonedSkull{}));
    }else if(c==celtic){
      cards.emplace_back(make_unique<CelticGuardian>(CelticGuardian{}));
    }else if(c==obelisk){
      cards.emplace_back(make_unique<Obelisk>(Obelisk{}));
    }else if(c==slifer){
      cards.emplace_back(make_unique<Slifer>(Slifer{}));
    }else if(c==ra){
      cards.emplace_back(make_unique<Ra>(Ra{}));
    }else if(c==darkMagician){
      cards.emplace_back(make_unique<DarkMagician>(DarkMagician{}));
    }else if(c==windGuard){
      cards.emplace_back(make_unique<WindGuardian>(WindGuardian{}));
    }else if(c==thunderGuard){
      cards.emplace_back(make_unique<ThunderGuardian>(ThunderGuardian{}));
    }else if(c==waterGuard){
      cards.emplace_back(make_unique<WaterGuardian>(WaterGuardian{}));
    }else{
      cout<<"Did you honestly think "<<c<<" was a real card?"<<endl;
    }
	  //no valid card
  }
}
