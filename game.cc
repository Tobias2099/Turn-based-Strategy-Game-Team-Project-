#ifndef __GAME_CC__
#define __GAME_CC__

#include <iostream>
#include <vector>
#include <string>
#include "game.h"

using namespace std;

Game::Game(Board *b, string turn, string winner, Player* p1, Player* p2, vector<AbstractEntity*> pieces):
  b{b}, turn{turn}, winner{winner}, p1{p1}, p2{p2}, pieces{pieces} {}

Game::~Game() {
  delete p1;
  delete p2;
  delete b;
  for (auto it = pieces.begin(); it != pieces.end(); ++it) {
      delete *it;
  }
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
  if (turn == "Player 1") {
    turn = "Player 2";
  } else if (turn == "Player 2"){
    turn = "Player 1";
  }
  //cout << " to " << turn << endl;
}

//FIX / CHANGE
void Game::printGameState() {
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
  const int maxData = 4;
  if (player == "Player 1"){
    p1->download(virus, data);
  } else if (player == "Player 2"){
    p2->download(virus, data);
  }

  if (p1->getData() >= maxData){
    setWinner("Player 1");
  }

  if (p2->getData() >= maxData){
    setWinner("Player 2");
  }
}

void Game::addEntityToBoard(AbstractEntity* entity){
    pieces.emplace_back(entity);
    b->setBoard(entity->getX(), entity->getY(), entity->getID());
}

bool Game::simplemove(string playerincontrol, int id, char dir){
    if (id < 0) {
        return false;
        //nomove
    }

    AbstractLink* to_move = pieces[id];

    if (!(to_move->isActive())) {
        cout << "Piece deactivated, can't move." << endl;
        return false;
    }

    AbstractLink* target = nullptr;
    size_t oldX = pieces[id]->getX();
    size_t oldY = pieces[id]->getY();

    int newX = 0;
    int newY = 0;
    
    //are we even allowed to move this piece?
    if (to_move->getType() == Type::Serverport || to_move->getOwner() != playerincontrol){
        cout << "Not allowed to move this piece!" << endl;
        return false;
    }

    //where are we going?
    if (dir == 'r'){
        newX = oldX + 1;
        newY = oldY;
    } else if (dir == 'l'){
        newX = oldX - 1;
        newY = oldY;
    } else if (dir == 'u'){
        newX = oldX;
        newY = oldY - 1;
    } else if (dir == 'd'){
        newX = oldX;
        newY = oldY + 1;
    }
    const int firstRow = 0;
    const int lastRow = 7;
    //did we walk off the board?
    if (newX >= static_cast<int>(width) || newX < firstRow || newY >= static_cast<int>(height) || newY < firstRow) {

        if (to_move->getOwner() == "Player 1" && newY > lastRow){
            to_move->deactivate();
            //do we reveal here?
            if (to_move->getType() == "V") {
                download(to_move->getOwner(),1,0);
            } else if (to_move->getType() == "D") {
                download(to_move->getOwner(),0,1);
            }
            b->setBoard(oldX, oldY, -1);
            return true;
        }

        if (to_move->getOwner() == "Player 2" && newY < firstRow){
            to_move->deactivate();
            //do we reveal here?
            if (to_move->getType() == "V"){
                download(to_move->getOwner(),1,0);
            } else if (to_move->getType() == "D"){
                download(to_move->getOwner(),0,1);
            }
            b->setBoard(oldX, oldY, -1);
            return true;
        }

        cout << "Tried to move off the board!" << endl;
        return false;
    }

    //who is there?
    target =  b->whoat(newX, newY);

    // if someone is there and we own it
    if (target != nullptr && target->getOwner() == playerincontrol){
        cout << "Can't move onto our own piece!" << endl;
        return false;
    } else if (target != nullptr && target->getType() == Type::Serverport) {
        //cout << "moved onto enemy serverport" << endl;
        string serverport_owner = target->getOwner();
        if (to_move->getType() == "V"){
            download(serverport_owner,1,0);
        } else if (to_move->getType() == "D"){
            download(serverport_owner,0,1);
        }
        to_move->deactivate();
        b->setBoard(oldX, oldY, -1);
        return true;

    } else if (target != nullptr && target->getOwner() != playerincontrol) {       
        // if we are trying to move onto someone else's piece
        int winningID = b->battle(to_move, target);

        if (winningID == to_move->getID()){
            //cout << "initator wins" << endl;
            to_move->setX(newX);
            to_move->setY(newY);
            target->deactivate();
            to_move->reveal();
            target->reveal();
            boardrep[newX][newY] = to_move->getID();
            boardrep[oldX][oldY] = -1;

            // to_move wins, to_move will download targets link
            string winnerowner = to_move->getOwner();

            //download
            if (target->getType() == "V"){
                download(winnerowner,1,0);
            } else if (to_move->getType() == "D"){
                download(winnerowner,0,1);
            }

            return true;
        } else {
            //lost the battle
            //cout << "defender wins" << endl;
            to_move->deactivate();
            to_move->reveal();
            target->reveal();
            b->boardrep[oldX][oldY] = -1;

            string winnerowner = target->getOwner();

            //download
            if (to_move->getType() == "V"){
                download(winnerowner,1,0);
            } else if (to_move->getType() == "D"){
                download(winnerowner,0,1);
            }

            return true;
        }
    }

    to_move->setX(newX);
    to_move->setY(newY);

    // change the internal board
    b->boardrep[newX][newY] = pieces[id]->getID();
    b->boardrep[oldX][oldY] = -1;

    return true;
}


int Game::appearanceToID(char c) {
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if ((*it)->getApp() == c){
            return (*it)->getID();
        }
    }
    return -1; // -1 if not found.
}

#endif


int Game::battle(AbstractLink* initiator, AbstractLink* defender) {
  if (initiator->getPower() >= defender->getPower()) {
    return initiator->getID();
  } else {
    return defender->getID();
  }
}