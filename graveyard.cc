#include "graveyard.h"


void Graveyard::addCard(std::unique_ptr<Card> newCard){
  std::cout<<newCard->getName()<<" just literally died"<<std::endl;
  graveyard.emplace_back(std::move(newCard));
}


void Graveyard::printCard(unsigned int idx){
  if(idx<graveyard.size()){
    graveyard[idx]->printCard();
  }
}


void Graveyard::printGraveyard(){
  for(unsigned int i = 0;i<graveyard.size();i++){
    printCard(i);
  }
}

bool Graveyard::notEmpty(){
  return !graveyard.empty();;
}

Card* Graveyard::gcard(){
	if(notEmpty()){
	  return graveyard.back().get();
	}else{
	  return nullptr;
	}
}

std::unique_ptr<Card> Graveyard::graverob(){
  std::unique_ptr<Card> temp = std::move(graveyard.back());
  graveyard.pop_back();
  return std::move(temp);
}
