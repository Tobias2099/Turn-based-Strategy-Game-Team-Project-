#ifndef DISPLAYTEXT_CC
#define DISPLAYTEXT_CC

#include "displayText.h"
#include "abstractentity.h"
#include <iostream>

// helper method
string convertTypeToString(Type type) {
  if (type == Type::Data) {
    return "D";
  } else if (type == Type::Serverport) {
    return "S";
  } else if (type == Type::Virus) {
    return "V";
  }
  return "X";
} 


displayText::displayText(Game* g) : g{g} {}

displayText::~displayText() {
  //detach?
}


void displayText::notify() {

  string playerName = g->getPlayer(); //getState() equivalent

  cout << "Player 1: " << endl;
  cout << "Downloaded: " << g->getFirstPlayer()->getData() << "D, " << g->getFirstPlayer()->getViruses() << "V" << endl;
  if (g->isEnhancementsEnabled()) {
    cout << "Abilities: " << (g->getFirstPlayer())->abilitiesleft() << " ";
    cout << (g->getFirstPlayer())->printabvec() << endl;
  } else {
    cout << "Abilities: " << (g->getFirstPlayer())->abilitiesleft() << " " << endl;
  }


  //todo: reveal if battled

  const int maxLinks = 8;
  const int breakPoint = 3;
  if (playerName == "Player 1"){
    //ids hardcoded. Change later?

    for (int i = 0; i < maxLinks; i++) {
      Link* link = dynamic_cast<Link*>(g->whoAt(i));
      cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
      << link->getPower() << " ";
      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      Link* link = dynamic_cast<Link*>(g->whoAt(i));
      if (link->isVisible()){
        cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
        << link->getPower() << " ";
      } else {
        cout << link->getAppearance() << ":  ? ";
      }

      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  }

  //ADD GETTERS HERE BELOW IN PRINT BOARD

  //PRINT BOARD
  for (int i = 0; i < g->getBoard()->getWidth(); i++) {
        cout << "=";
    }
    cout << endl;
    for (int i = 0; i < g->getBoard()->getHeight(); i++)
    {
        for (int j = 0; j < g->getBoard()->getWidth(); j++)
        {   
            int boardID = g->getBoard()->getValue(j, i);
            if (boardID == -1){
                cout << '.';
            } else {
                cout << g->getPieces()[boardID]->getAppearance();
            }
        }    
        cout << endl;
    }
    for (int i = 0; i < g->getBoard()->getWidth(); i++){
        cout << "=";
    }
    cout << endl;


  cout << "Player 2: " << endl;
  cout << "Downloaded: " << g->getSecondPlayer()->getData() << "D, " << g->getSecondPlayer()->getViruses() << "V" << endl;
  if (g->isEnhancementsEnabled()) {
    cout << "Abilities: " << (g->getSecondPlayer())->abilitiesleft();
    cout << " " << (g->getSecondPlayer())->printabvec() << endl;
  } else {
    cout << "Abilities: " << (g->getSecondPlayer())->abilitiesleft() << endl;
  }


  if (playerName == "Player 2"){
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++) {
      Link* link = dynamic_cast<Link*>(g->whoAt(i + maxLinks));
      cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
      << link->getPower() << " ";
      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      Link* link = dynamic_cast<Link*>(g->whoAt(i + maxLinks));
      if (link->isVisible()){
        cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
        << link->getPower() << " ";
      } else {
        cout << link->getAppearance() << ":  ? ";
      }

      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  }
}

#endif
