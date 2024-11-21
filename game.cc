#ifndef __GAME_CC__
#define __GAME_CC__

#include <iostream>
#include <vector>
#include <string>
#include "game.h"

using namespace std;

Game::Game(Board *b, string turn, string winner, Player* p1, Player* p2):
  b{b}, turn{turn}, winner{winner}, p1{p1}, p2{p2} {}

Game::~Game() {
  delete p1;
  delete p2;
  delete b;
}

string Game::getWinner(){
  return winner;
}
string Game::getTurn(){
  return turn;
}
Board* Game::getBoard(){
  return b;
}

void Game::setWinner(string w){
  winner = w;
}

void Game::advance(){
  //cout << "going from " << turn;
  if (turn == "Player 1"){
    turn = "Player 2";
  }else if (turn == "Player 2"){
    turn = "Player 1";
  }
  //cout << " to " << turn << endl;
}

void Game::printGameState(){
  cout << "Player 1: " << endl;
  cout << "Downloaded: " << p1->getData() << "D, " << p1->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  //todo: reveal if battled

  if (turn == "Player 1"){
    //ids hardcoded. Change later?
    for (int i = 0; i < 8; i++){
      cout << (b->whoat(i))->getApp() << ": " << (b->whoat(i))->getType() 
      << (b->whoat(i))->getPower() << " ";
      if (i == 3) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 0; i < 8; i++){

      if ((b->whoat(i))->isvisible()){
        cout << (b->whoat(i))->getApp() << ": " << (b->whoat(i))->getType() 
        << (b->whoat(i))->getPower() << " ";
      } else {
        cout << (b->whoat(i))->getApp() << ":  ? ";
      }

      if (i == 3) cout << endl;
    }
    cout << endl;
  }

  //DELETED b->printBoard();

  cout << "Player 2: " << endl;
  cout << "Downloaded: " << p2->getData() << "D, " << p2->getViruses() << "V" << endl;
  cout << "Abilities (later)" << endl;

  if (turn == "Player 2"){
    //ids hardcoded. Change later?
    for (int i = 8; i < 16; i++){
      cout << (b->whoat(i))->getApp() << ": " << (b->whoat(i))->getType() 
      << (b->whoat(i))->getPower() << " ";
      if (i == 11) cout << endl;
    }
    cout << endl;
  } else {
    //ids hardcoded. Change later?
    for (int i = 8; i < 16; i++){
      
      if ((b->whoat(i))->isvisible()){
        cout << (b->whoat(i))->getApp() << ": " << (b->whoat(i))->getType() 
        << (b->whoat(i))->getPower() << " ";
      } else {
        cout << (b->whoat(i))->getApp() << ":  ? ";
      }

      if (i == 11) cout << endl;
    }
    cout << endl;
  }

}

void Game::download(string player, int virus, int data){
  if (player == "Player 1"){
    p1->download(virus, data);
  } else if (player == "Player 2"){
    p2->download(virus, data);
  }

  if (p1->getData() >= 4){
    setWinner("Player 1");
  }

  if (p2->getData() >= 4){
    setWinner("Player 2");
  }
}

#endif