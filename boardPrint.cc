#include "ascii_graphics.h"
#include "player.h"
void Board::print(int playerNum){

if(playerNum == 1) {
  std::vector<card_template_t> cardList;
  
  Card * deadCard = owner->gdead();
  
  card_template_t pcard;
  card_template_t rcard;
  if(ritual.empty()) {
	rcard = CARD_TEMPLATE_BORDER;
  } else {
	Ritual * R_temp;
	R_temp = (Ritual *) ritual[0].get();
	rcard = display_ritual(R_temp->getName(),R_temp->getCost(),R_temp->getActivationCost(),R_temp->getDescription(), R_temp->getCharges());
  }
  if(deadCard == nullptr) {
	pcard = CARD_TEMPLATE_BORDER;
  } else {
  if(deadCard->getType() == "minion"){
  	Minion * M_temp;
	M_temp = (Minion *) deadCard;  
     if(M_temp->hasTriggeredAbility()) {
	pcard = display_minion_triggered_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getDescription());
     } else if(M_temp->hasActivatedAbility()){
       pcard= display_minion_activated_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getAbilityCost(),M_temp->getDescription());
     }else{
       pcard = display_minion_no_ability(M_temp->getName(), M_temp->getCost(), M_temp->getAttack(), M_temp->getDefence());
     }
  }
  }

  
  card_template_t playerCard;
  playerCard = display_player_card(1,owner->getName(),owner->getHealth(), owner->getMagic());
 
  int card_dimensions = 11;

  cardList.emplace_back(pcard);
  cardList.emplace_back(CARD_TEMPLATE_EMPTY);
  cardList.emplace_back(playerCard);
  cardList.emplace_back(CARD_TEMPLATE_EMPTY);
  cardList.emplace_back(rcard);
  
  for(int i = 0; i < card_dimensions; i++){
	std::string printer;
	for(unsigned int j = 0; j < cardList.size(); j++){
		printer = printer + cardList[j][i];
		
	}
	printer = "|"+printer+"|";
	std::cout<<printer<<std::endl;
  }
  for(unsigned int i = 0; i < cardList.size(); i++){
	cardList[i].clear();
  }
  cardList.clear();
  if(minions.empty()){
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      
  } else {
      for(unsigned int i = 0; i < minions.size(); i++) {
	  Minion * M_temp;
	  M_temp  = (Minion *) minions[i].get(); 
	  
	  if(M_temp->hasTriggeredAbility()) {
	    card_template_t m_card = display_minion_triggered_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getDescription());
	    cardList.emplace_back(m_card);
	  } else if(M_temp->hasActivatedAbility()){
	    card_template_t m_card= display_minion_activated_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getAbilityCost(),M_temp->getDescription());
	    cardList.emplace_back(m_card);
	  }else{
	    card_template_t m_card = display_minion_no_ability(M_temp->getName(), M_temp->getCost(), M_temp->getAttack(), M_temp->getDefence());
	    cardList.emplace_back(m_card);
	  }
      }

      for(unsigned int i = 0; i < 5 - minions.size(); i++) {
	  cardList.emplace_back(CARD_TEMPLATE_BORDER);
      } 
  }

  for(int i = 0; i < card_dimensions; i++){
	std::string printer;
	for(unsigned int j = 0; j < cardList.size(); j++){
		printer = printer + cardList[j][i];
	}
	printer = "|"+printer+"|";
	std::cout<<printer<<std::endl;
  }

  for(unsigned int i = 0; i < cardList.size(); i++){
	cardList[i].clear();
  }
  cardList.clear();


} else if(playerNum == 2) {
  


  const int card_dimensions = 11;	
  std::vector<card_template_t> cardList;
  if(minions.empty()){
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      cardList.emplace_back(CARD_TEMPLATE_BORDER);
      
  } else {
      for(unsigned int i = 0; i < minions.size(); i++) {
	Minion * M_temp;
	M_temp  = (Minion *) minions[i].get(); 
	
	if(M_temp->hasTriggeredAbility()) {
	  card_template_t m_card = display_minion_triggered_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getDescription());
	  cardList.emplace_back(m_card);
	} else if(M_temp->hasActivatedAbility()){
	  card_template_t m_card= display_minion_activated_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getAbilityCost(),M_temp->getDescription());
	  cardList.emplace_back(m_card);
	}else{
	  card_template_t m_card = display_minion_no_ability(M_temp->getName(), M_temp->getCost(), M_temp->getAttack(), M_temp->getDefence());
	  cardList.emplace_back(m_card);
	}
      }

      for(unsigned int i = 0; i < 5 - minions.size(); i++) {
	  cardList.emplace_back(CARD_TEMPLATE_BORDER);
      } 
  }

  for(unsigned int i = 0; i < card_dimensions; i++){
	std::string printer;
	for(unsigned int j = 0; j < cardList.size(); j++){
		printer = printer + cardList[j][i];
	}
	printer = "|"+printer+"|";
	std::cout<<printer<<std::endl;
  }

  for(unsigned int i = 0; i < cardList.size(); i++){
	cardList[i].clear();
  }
  cardList.clear();

  Card * deadCard = owner->gdead();
  
  card_template_t pcard;
  card_template_t rcard;
  if(ritual.empty()) {
	rcard = CARD_TEMPLATE_BORDER;
  } else {
	Ritual * R_temp;
	R_temp = (Ritual *) ritual[0].get();
	rcard = display_ritual(R_temp->getName(),R_temp->getCost(),R_temp->getActivationCost(),R_temp->getDescription(), R_temp->getCharges());
  }
  if(deadCard == nullptr) {
	pcard = CARD_TEMPLATE_BORDER;
  } else {
    if(deadCard->isMinion()){
  	Minion * M_temp;
	M_temp = (Minion *) deadCard;  
    if(M_temp->hasTriggeredAbility()) {
	pcard = display_minion_triggered_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getDescription());
     } else if(M_temp->hasActivatedAbility()){
       pcard= display_minion_activated_ability(M_temp->getName(),M_temp->getCost(),M_temp->getAttack(),M_temp->getDefence(),M_temp->getAbilityCost(),M_temp->getDescription());
     }else{
       pcard = display_minion_no_ability(M_temp->getName(), M_temp->getCost(), M_temp->getAttack(), M_temp->getDefence());
     }
    } 
  }


  
  card_template_t playerCard;
  playerCard = display_player_card(2,owner->getName(),owner->getHealth(), owner->getMagic());
 

  cardList.emplace_back(rcard);
  cardList.emplace_back(CARD_TEMPLATE_EMPTY);
  cardList.emplace_back(playerCard);
  cardList.emplace_back(CARD_TEMPLATE_EMPTY);
  cardList.emplace_back(pcard);
  
  for( int i = 0; i < card_dimensions; i++){
	std::string printer;
	for(unsigned int j = 0; j < cardList.size(); j++){
	  printer = printer + cardList[j][i];
	}
	printer = "|"+printer+"|";
	std::cout<<printer<<std::endl;
  }
  for(unsigned int i = 0; i < cardList.size(); i++){
    cardList[i].clear();
  }
  cardList.clear();
  }
  

}
