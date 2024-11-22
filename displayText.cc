#ifndef DISPLAYTEXT_CC
#define DISPLAYTEXT_CC

#include "displayText.h"
#include "abstractentity.h"
#include <iostream>

// helper method
string convertTypeToString(Type type) {
  if (type == Type::Data) {
    return "Data";
  } else if (type == Type::Serverport) {
    return "Severport";
  } else if (type == Type::Virus) {
    return "Virus";
  }
} 


displayText::displayText(Game* g) : g{g} {}

displayText::~displayText() {
  delete g;
}


void displayText::notify() {

  string playerName = g->getPlayer(); //getState() equivalent

  cout << "Player 1: " << endl;
  cout << "Downloaded: " << g->getFirstPlayer()->getData() << "D, " << g->getSecondPlayer()->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  //todo: reveal if battled

  const int maxLinks = 8;
  const int breakPoint = 3;
  if (playerName == "Player 1"){
    //ids hardcoded. Change later?

    for (int i = 0; i < maxLinks; i++) {
      AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i));
      cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
      << link->getPower() << " ";
      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i));
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
  for (size_t i = 0; i < g->getBoard()->getWidth(); i++) {
        cout << "=";
    }
    cout << endl;
    for (size_t i = 0; i < g->getBoard()->getHeight(); i++)
    {
        for (size_t j = 0; j < g->getBoard()->getWidth(); j++)
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
    for (size_t i = 0; i < g->getBoard()->getWidth(); i++){
        cout << "=";
    }
    cout << endl;


  cout << "Player 2: " << endl;
  cout << "Downloaded: " << g->getSecondPlayer()->getData() << "D, " << g->getSecondPlayer()->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  if (playerName == "Player 2"){
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++) {
      AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i + maxLinks));
      cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
      << link->getPower() << " ";
      if (i == breakPoint + maxLinks) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i + maxLinks));
      if (link->isVisible()){
        cout << link->getAppearance() << ": " << convertTypeToString(link->getType())
        << link->getPower() << " ";
      } else {
        cout << link->getAppearance() << ":  ? ";
      }

      if (i == breakPoint + maxLinks) cout << endl;
    }
    cout << endl;
  }
}

#endif