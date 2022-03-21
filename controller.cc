#include "controller.h"
using namespace std;

void Controller::init(){
  int numCards = 5;
  for(int i = 0;i<numCards;i++){
    activePlayer->draw();
    nonActivePlayer->draw();
  }
}

Controller::Controller(string p1, string p2,vector<string> deck1list,vector<string> deck2list,bool testing){
  Player1 = make_unique<Player>(p1,deck1list,testing);
  Player2 = make_unique<Player>(p2,deck2list,testing);
  activePlayer = Player1.get();
  nonActivePlayer = Player2.get();
  testing = testing;
}


void Controller::switchPlayers(){
  activePlayer->eot(activePlayer,nonActivePlayer);
  std::swap(activePlayer,nonActivePlayer);
  activePlayer->beginTurn(activePlayer,nonActivePlayer);
}

std::string Controller::whosTurn(){
  return activePlayer->getName();
}

void Controller::draw(int i){
  for(int j = 0;j<i;j++){
    activePlayer->draw();
  }
}

void Controller::discard(int i){
  if(i>0&&i<6){
    activePlayer->discard(i-1);
  }else{
    std::cerr<<"Out of range arguments given to discard"<<std::endl;
  }
}

void Controller::attack(int i){
  i-=1;
  if(i<0){
    std::cerr<<"Index must be greater than 0"<<std::endl;
    return;
  }
  //Check if valid board->isValid(activePlayer,i)
  if(nonActivePlayer->defenceless()){
    if(activePlayer->hasMinion(i)){
      if(activePlayer->canAttack(i)){
	nonActivePlayer->defend(activePlayer->getMinion(i));
      }
    }else{
      std::cerr<<"No minion exists as that index"<<std::endl;
      return;
    }
  }else{
    std::cerr<<nonActivePlayer->getName()<<" can't be directly attacked, since they still have monsters defending them"<<std::endl;
  }
}

void Controller::attack(int i, int j){
  i-=1;
  j-=1;
  if(i<0||j<0){
    std::cerr<<"Index must be greater than 0"<<std::endl;
  }
  // board hasMoves(activePlayer,i)
  if(activePlayer->hasMinion(i)&&nonActivePlayer->hasMinion(j)){
    if(activePlayer->canAttack(i)){
      nonActivePlayer->defendAgainst(j,activePlayer->getMinion(i));
      activePlayer->defendAgainst(i,nonActivePlayer->getMinion(j));
      nonActivePlayer->resolve(nonActivePlayer,activePlayer);
      activePlayer->resolve(activePlayer,nonActivePlayer);
    }
  }else{
    std::cerr<<"Invalid indexes for attack"<<std::endl;
  }
}

void Controller::play(int i){
  //Check if the card exists in hand, and if there are open space on the board to play it
  i-=1;
  if(i<0){
    std::cerr<<"Index must be greater than 0"<<std::endl;
    return;
  }
  activePlayer->play(i,nonActivePlayer);
  activePlayer->resolve(activePlayer,nonActivePlayer);
  nonActivePlayer->resolve(nonActivePlayer,activePlayer);
}

void Controller::play(int i, int p, int target){
  i-=1;
  target-=1;
  if(i<0){
    std::cerr<<"Index must be a positive number"<<std::endl;
    return;
  }
  activePlayer->play(i,p,target,activePlayer,nonActivePlayer);
  activePlayer->resolve(activePlayer,nonActivePlayer);
  nonActivePlayer->resolve(nonActivePlayer,activePlayer);
}


void Controller::use(int i, int p, int target){
  i-=1;
  if(i<0){
    std::cerr<<"Index must be a positive number"<<std::endl;
    return;
  }
  activePlayer->use(i,p,target,activePlayer,nonActivePlayer);
}

void Controller::describe(int i){
  if(i<1||i>5){
    std::cerr<<"Invalid range to describe"<<std::endl;
    return;
  }
  activePlayer->describe(i-1);
}

void Controller::displayHand(){
  activePlayer->printHand();
}

void Controller::displayBoard(){
  
  string dashes = "";
  for(int i = 0; i < 167; i++) {
  	dashes = dashes + "-";
  }	  
  cout<< dashes <<endl;
  nonActivePlayer->printBoard(1);
  
  ifstream Reader;
  Reader.open("asciiart.txt");
  string line = "";
  while(getline(Reader, line)) {
	cout<<line<<endl;
  }
  Reader.close();
     
  activePlayer->printBoard(2);
  
  cout<< dashes <<endl;

}

void Controller::printActiveDeck(){
  activePlayer->printDeck();
}

void Controller::shuffle(int n){
  if(n==1){
    activePlayer->shuffle();
  }else if(n==2){
    nonActivePlayer->shuffle();
  }
}

void Controller::printGraveyard(){
  activePlayer->printGraveyard();
}

bool Controller::gameOver(){
  std::string who = "";
  
  if(activePlayer->isDead()){
    who = nonActivePlayer->getName();
  }else if(nonActivePlayer->isDead()){
    who = activePlayer->getName();
  }
  if(who!=""){
   /* std::cout<<"------------"<<std::endl<<std::endl;
    std::cout<<who<<" Wins!"<<std::endl<<std::endl;
    std::cout<<"------------"<<std::endl;*/
    ifstream Reader;
    Reader.open("ASCIIART_VICTORY.txt");
    string line = "";
    while(getline(Reader, line)) {
   	  cout<<line<<endl;
    }
    cout<<endl;
    Reader.close();     
    return 1;
  }else{
    return 0;
  }
}

void Controller::setPlayers(){
  activePlayer->setOppon(nonActivePlayer);
  nonActivePlayer->setOppon(activePlayer);  
}
