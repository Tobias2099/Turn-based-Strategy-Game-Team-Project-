#ifndef DISPLAYTEXT_CC
#define DISPLAYTEXT_CC

#include "displayText.h"
#include <iostream>

displayText::displayText(Game* g) : g{g} {}

displayText::~displayText() {
  delete g;
}

void displayText::notify() {

  string playerName = g->getPlayer(); //getState() equivalent
  
  cout << "Player 1: " << endl;
  cout << "Downloaded: " << p1->getData() << "D, " << p1->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  //todo: reveal if battled

  const int maxLinks = 8;
  const int breakPoint = 3;
  if (playerName == "Player 1"){
    //ids hardcoded. Change later?

    for (int i = 0; i < maxLinks; i++){
      cout << (g->whoAt(i))->getAppearance() << ": " << (g->whoAt(i))->getType() 
      << (g->whoAt(i))->getPower() << " ";
      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){

      if ((this->whoAt(i))->isvisible()){
        cout << (this->whoAt(i))->getApp() << ": " << (this->whoAt(i))->getType() 
        << (this->whoAt(i))->getPower() << " ";
      } else {
        cout << (this->whoAt(i))->getApp() << ":  ? ";
      }

      if (i == breakPoint) cout << endl;
    }
    cout << endl;
  }

  //PRINT BOARD
  for (size_t i = 0; i < g->getBoard()->width; i++) {
        cout << "=";
    }
    cout << endl;
    for (size_t i = 0; i < g->getBoard()->height; i++)
    {
        for (size_t j = 0; j < g->getBoard()->width; j++)
        {   
            int boardID = g->getBoard()->getValue(j, i);
            if (boardID == -1){
                cout << '.';
            } else {
                cout << pieces[boardID]->getAppearance();
            }
        }    
        cout << endl;
    }
    for (size_t i = 0; i < g->getBoard()->width; i++){
        cout << "=";
    }
    cout << endl;


  cout << "Player 2: " << endl;
  cout << "Downloaded: " << p2->getData() << "D, " << p2->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  if (playerName == "Player 2"){
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      cout << (this->whoAt(i + maxLinks))->getApp() << ": " << (this->whoAt(i + maxLinks))->getType() 
      << (this->whoAt(i + maxLinks))->getPower() << " ";
      if (i == breakPoint + maxLinks) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < maxLinks; i++){
      
      if ((this->whoAt(i + maxLinks))->isvisible()){
        cout << (this->whoAt(i + maxLinks))->getApp() << ": " << (this->whoAt(i + maxLinks))->getType() 
        << (this->whoAt(i + maxLinks))->getPower() << " ";
      } else {
        cout << (this->whoAt(i + maxLinks))->getApp() << ":  ? ";
      }

      if (i == breakPoint + maxLinks) cout << endl;
    }
    cout << endl;
  }
}

#endif