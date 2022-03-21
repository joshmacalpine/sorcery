#include "hand.h"
#include "ascii_graphics.h"

#include "minion.h"
#include "spells.h"
#include "ritual.h"
#include "enchantments.h"


void Hand::addCard(std::unique_ptr<Card> newCard){
  hand.emplace_back(std::move(newCard));
}

void Hand::discard(unsigned int idx){
  if(idx<hand.size()){
    takeCard(idx);
  }else{
    std::cerr<<"Can't discard something that doesn't exist"<<std::endl;
  }
}

void Hand::printCard(unsigned int idx){
  if(idx<hand.size()){

  }else{
    std::cerr<<"index out of range"<<std::endl;
  }
}

void Hand::printHand(){
// to print side by side
// i want to store each "line" of the card into a string
// then print each mega-line 1 by 1

	//helper function
	const int card_dimensions = 11;

	std::vector<card_template_t> cardlist;


	for(unsigned int i = 0;i<hand.size();i++){

		if(hand[i]->getType() == "minion") {
			Minion* M_temp; // casting stuff
			M_temp = (Minion*)hand[i].get();
			if(M_temp->canAbil() == true) {
				if(M_temp->hasTriggeredAbility() == true) {
					card_template_t pcard = display_minion_triggered_ability(M_temp->getName(),M_temp->getCost(), M_temp->getAttack(), 
																		M_temp->getDefence(), M_temp->getDescription());
					cardlist.emplace_back(pcard);
					}
				
				else if(M_temp->hasActivatedAbility() == true) {
					card_template_t pcard = display_minion_activated_ability(M_temp->getName(),M_temp->getCost(), M_temp->getAttack(), 
																		M_temp->getDefence(), M_temp->getAbilityCost(), M_temp->getDescription());
					cardlist.emplace_back(pcard);

				} else {
					card_template_t pcard = display_minion_no_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence());
					cardlist.emplace_back(pcard);
				}

			}
			else {
					card_template_t pcard = display_minion_no_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence());
					//for(unsigned int j = 0; j < pcard.size(); j++) {
					//	std::cout<<pcard[j]<<std::endl;;
					//}
					cardlist.emplace_back(pcard);
			}	
		}

		if(hand[i]->getType() == "spell") {
			Spell* S_temp;
			S_temp = (Spell*)hand[i].get();
			card_template_t pcard = display_spell(S_temp->getName(), S_temp->getCost(), S_temp->getDescription());
			cardlist.emplace_back(pcard);
		}

		if(hand[i]->getType() == "ritual") {
			Ritual* R_temp;
			R_temp = (Ritual*)hand[i].get();
			card_template_t pcard = display_ritual(R_temp->getName(),R_temp->getCost(),R_temp->getActivationCost(), 
													R_temp->getDescription(), R_temp->getCharges());
			cardlist.emplace_back(pcard);
			
		}
		
		if(hand[i]->getType() == "enchantment") {
		  Enchantment* E_temp;
		  card_template_t pcard;
		  E_temp = (Enchantment*)hand[i].get();
		  if(E_temp->getAttack()==""){
		    pcard = display_enchantment(E_temp->getName(), E_temp->getCost(), E_temp->getDescription());
		  }else{
		    pcard = display_enchantment_attack_defence(E_temp->getName(),E_temp->getCost(),E_temp->getDescription(),E_temp->getAttack(),E_temp->getDefence());
		  }
		  cardlist.emplace_back(pcard);
		}
	}
	
	int clenlist = cardlist.size();
	int ccount = 0;
	while(clenlist > 0) {
		for(int i = 0; i < card_dimensions; i++) {
			std::string printer;
			if(clenlist >= 5) {
				for(int j = 0; j < 5; j++) {
					printer = printer + cardlist[j+ccount][i];
				}	
				std::cout<<printer<<std::endl;;
			} else {
				for(int j = 0; j < clenlist; j++) {
					printer = printer + cardlist[j+ccount][i];
				}
				std::cout<<printer<<std::endl;;
			}
		}
		clenlist = clenlist - 5;
		ccount = ccount + 5;
		std::cout<<std::endl;;
	}


      

}

Card* Hand::ithCard(unsigned int i){
  if(i<hand.size()){
    return hand[i].get();
  }else{
    return nullptr;
  }
}

std::unique_ptr<Card> Hand::takeCard(int i){
  std::unique_ptr<Card> temp = std::move(hand[i]);
  hand.erase(hand.begin()+i);
  return std::move(temp);
}

int Hand::getSize(){
  return hand.size();
}
