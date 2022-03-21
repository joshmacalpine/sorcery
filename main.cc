#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "controller.h"

int main(int argc,char** argv){
  bool testing = 0;
  std::string initMode = "-init";
  std::string deck1Mode = "-deck1";
  std::string deck2Mode = "-deck2";
  std::string testingMode = "-testing";
  bool deck1 = 0;
  bool deck2 = 0;
  bool init = 0;
  std::string deck1file;
  std::string deck2file;
  std::string initfile;
  std::vector<std::string> deck1list;
  std::vector<std::string> deck2list;
  for(int i = 0;i<argc;i++){
    if(argv[i]==initMode&&!init){
      if(i>=(argc-1)||argv[i+1]==initMode||argv[i+1]==deck2Mode||argv[i+1]==testingMode||argv[i+1]==deck1Mode){
	std::cerr<<"No file name provided after -init"<<std::endl;
      }else{
	i++;
	initfile = argv[i];
        init = 1;
      }
    }else if (argv[i]==deck1Mode&&!deck1){
      if(i>=(argc-1)||argv[i+1]==initMode||argv[i+1]==deck2Mode||argv[i+1]==testingMode||argv[i+1]==deck1Mode){
	std::cerr<<"No file name provided after -deck1"<<std::endl;
      }else{
	i++;
	deck1file = argv[i];
	deck1 = 1;
      }
    }else if(argv[i]==deck2Mode&&!deck2){
      if(i>=(argc-1)||argv[i+1]==initMode||argv[i+1]==deck2Mode||argv[i+1]==testingMode||argv[i+1]==deck1Mode){
	std::cerr<<"No file name provided after -deck2"<<std::endl;
      }else{
	i++;
	deck2file = argv[i];
	deck2 = 1;
      }
    }else if(argv[i]==testingMode&&!testing){
      testing = 1;
      std::cout<<"In testing mode"<<std::endl;
    }    
  }

  if(deck1file==""){
    deck1file = "default.deck";
  }
  if(deck2file==""){
    deck2file="default.deck";
  }

  std::fstream deck1stream{deck1file};
  std::fstream deck2stream{deck2file};
  std::fstream initstream{initfile};
  std::string card;

  while(std::getline(deck1stream, card)){
    deck1list.emplace_back(card);
  }

  if(deck1list.size()<5&&!testing){
    std::cerr<<"Player 1's deck is less than 5 cards, switching to default deck instread"<<std::endl;
    deck1list.clear();
    deck1stream = std::fstream{"default.deck"};
    while(std::getline(deck1stream,card)){
      deck1list.emplace_back(card);
    }
  }
  
  while(std::getline(deck2stream, card)){
    deck2list.emplace_back(card);
  }

  if(deck2list.size()<5&&!testing){
    std::cerr<<"Player 2's deck is less than 5 cards, switching to default deck instead"<<std::endl;
    deck2list.clear();
    deck2stream = std::fstream{"default.deck"};
    while(std::getline(deck2stream,card)){
      deck2list.emplace_back(card);
    }
  }
  
  std::string s;
  std::string p1;
  std::string p2;
  if(!std::getline(initstream,p1)){
    std::cout<<"Player 1's name?"<<std::endl;
    std::getline(std::cin, p1);
  }
  if(!std::getline(initstream,p2)){
    std::cout<<"Player 2's name?"<<std::endl;
    std::getline(std::cin, p2);
  }

  std::unique_ptr<Controller> controller = std::make_unique<Controller>(p1,p2,deck1list,deck2list,testing);

  if(!testing){
    controller->shuffle(1);
    controller->shuffle(2);
  }
  
  controller->init();
  controller->setPlayers();
  
  while(std::getline(initstream,s)||std::getline(std::cin, s)){
    std::istringstream iss{s};

    
    std::string cmd;
    std::vector<std::string> args;
    iss >> cmd;
    
    if (cmd == "help"){
      
      std::cout<<"Commands: help -- Display this message."<<std::endl;
      std::cout<<"\t  end -- End the current player's turn."<<std::endl;
      std::cout<<"\t  quit -- End the game."<<std::endl;
      std::cout<<"\t  attack minion other-minion -- Orders minion to attack other-minion."<<std::endl;
      std::cout<<"\t  attack minion -- Orders minion to attack the opponenet."<<std::endl;
      std::cout<<"\t  play card [target-player target-card] -- Play card, optionaly targeting target-card owned by target-player."<<std::endl;
      std::cout<<"\t  use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player."<<std::endl;
      std::cout<<"\t  inspect minion -- View a minion's card and all enchantments on that minion."<<std::endl;
      std::cout<<"\t  hand -- Describe all cards in your hand."<<std::endl;
      std::cout<<"\t  board -- Describe all cards on the board."<<std::endl;
      
    }else if(cmd == "end"){
      
      controller->switchPlayers();
      std::cout<<controller->whosTurn()<<"'s turn"<<std::endl;
      
    }else if(cmd == "quit"){
      return 0;
      
    }else if(cmd == "draw"&&testing){
      
      controller->draw(1);
      
    }else if(cmd == "discard"&&testing){
      
      std::string which;
      try{
	if(iss>>which){
	  int num = std::stoi(which);
	  controller->discard(num);
	}else{
	  std::cerr<<"No argument given to command discard"<<std::endl;
	}
      }catch (...){
	std::cerr<<"Invalid argument given to command discard"<<std::endl;
      }
      
    }else if(cmd == "attack"){
      std::string which;
      while(iss>>which && args.size()<2){
	args.emplace_back(which);
      }
      try{
	if(args.size()==2){
	  int attacker = std::stoi(args[0]);
	  int defender = std::stoi(args[1]);
	  controller->attack(attacker,defender);
	}else if(args.size()==1){
	  int attacker = std::stoi(args[0]);
	  controller->attack(attacker);
	}else{
	  std::cerr<< "Attack must have at least one argument" << std::endl;
	}
      }catch (...){
	std::cerr<<"Invalid arguments given to command attack"<<std::endl;
      }
            
    }else if(cmd == "play"){
      
      std::string which;
      while(iss>>which && args.size()<3){
	args.emplace_back(which);
      }
      try{
	if(args.size()==3){
	  int user = std::stoi(args[0]);
	  int player = std::stoi(args[1]);
	  int target = 0;
	  if(args[2]=="r"){
	    target = 6;
	  }else{
	    target = std::stoi(args[2]);
	    if(target>=6||target<=0){
	      throw std::invalid_argument("");
	    }
	  }
	  if(player!=1&&player!=2){
	    std::cerr<<"Second argument must be either 1 or 2"<<std::endl;
	  }else{
	    controller->play(user,player,target);
	  }
	}else if(args.size()==1){
	  int toPlay = std::stoi(args[0]);
	  controller->play(toPlay);
	}else{
	  std::cerr<< "Invalid number of arguments to command play" << std::endl;
	}
      }catch (...){
	std::cerr<<"Invalid arguments given to command play"<<std::endl;
      }
      
    }else if(cmd == "use"){
      

      std::string which;
      while(iss>>which && args.size()<3){
	args.emplace_back(which);
      }
      try{
	if(args.size()==3){
	  int user = std::stoi(args[0]);
	  int player = std::stoi(args[1]);
	  int target = 0;
	  if(args[2]=="r"){
	    target = 6;
	  }else{
	    target = std::stoi(args[2]);
	    if(target>=6||target<=0){
	      throw std::invalid_argument("");
	    }
	  }

	  
	  if(player!=1&&player!=2){
	    std::cerr<<"Second argument must be either 1 or 2"<<std::endl;
	  }else{
	    controller->use(user,player,target);
	  }
	}else if(args.size()==1){
	  int user = std::stoi(args[0]);
	  controller->use(user,0,1);
	}else{
	  std::cerr<< "Invalid number of arguments to command use" << std::endl;
	}
      }catch (...){
	std::cerr<<"Invalid arguments given to command use"<<std::endl;
      }
      
      
    }else if(cmd == "inspect"){
      std::string which;
      try{
	if(iss>>which){
	  int num = std::stoi(which);
	  controller->describe(num);
	}else{
	  std::cerr<<"No argument given to command inspect"<<std::endl;
	}
      }catch (...){
	std::cerr<<"Invalid argument given to command inspect"<<std::endl;
      }
    }else if(cmd == "hand"){
      
      controller->displayHand();
      
    }else if(cmd == "board"){
      
      controller->displayBoard();
      ///After this is all testing methods, which don't have a nice user interface 
    }else if(cmd == "deck"&&testing){
      controller->printActiveDeck();
    }else if(cmd=="shuffle"&&testing){
      controller->shuffle(1);
    }else if(cmd=="graveyard"&&testing){
      controller->printGraveyard();
    }else if (cmd != ""){
      
      std::cerr<< "Not a valid command" <<std::endl;
      
    }
    if(controller->gameOver()){
      return 0;
    }
  }

}
