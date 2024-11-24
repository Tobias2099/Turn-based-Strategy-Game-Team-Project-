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

vector<AbstractEntity*> Game::getPieces() {
  return pieces;
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

bool Game::simplemove(string playerincontrol, int id, char dir, int steps){
    if (id < 0 || id >= 16) {
        return false;
        //nomove, id's greater than 16 are serverports.
    }

    AbstractLink* to_move = dynamic_cast<AbstractLink*>(pieces[id]);

    if (steps == -1) {
      steps = to_move->getMoveCount();
    }

    if (!(to_move->isActive())) {
        cout << "Piece deactivated, can't move." << endl;
        return false;
    }

    AbstractEntity* target = nullptr;
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
        newX = oldX + steps;
        newY = oldY;
    } else if (dir == 'l'){
        newX = oldX - steps;
        newY = oldY;
    } else if (dir == 'u'){
        newX = oldX;
        newY = oldY - steps;
    } else if (dir == 'd'){
        newX = oldX;
        newY = oldY + steps;
    } else {
        cout << "Direction not recognized." << endl;
        return false;
    }

    const int firstRow = 0;
    const int lastRow = 7;
    //did we walk off the board?
    if (newX >= static_cast<int>(b->getWidth()) || newX < firstRow || newY >= static_cast<int>(b->getHeight()) || newY < firstRow) {

        if (to_move->getOwner() == "Player 1" && newY > lastRow){
            to_move->deactivate();
            //do we reveal here?
            if (to_move->getType() == Type::Virus) {
                download(to_move->getOwner(),1,0);
            } else if (to_move->getType() == Type::Data) {
                download(to_move->getOwner(),0,1);
            }
            b->setBoard(oldX, oldY, -1);
            return true;
        }

        if (to_move->getOwner() == "Player 2" && newY < firstRow){
            to_move->deactivate();
            //do we reveal here?
            if (to_move->getType() == Type::Virus){
                download(to_move->getOwner(),1,0);
            } else if (to_move->getType() == Type::Data){
                download(to_move->getOwner(),0,1);
            }
            b->setBoard(oldX, oldY, -1);
            return true;
        }

        cout << "Tried to move off the board!" << endl;
        return false;
    }

    //who is there?
    target =  this->whoAt(newX, newY);

    // if someone is there and we own it
    if (target != nullptr && target->getType() != Type::Firewall && target->getOwner() == playerincontrol){
        cout << "Can't move onto our own piece!" << endl;
        return false;
    } else if (target != nullptr && target->getType() == Type::Serverport) {
        //cout << "moved onto enemy serverport" << endl;
        string serverport_owner = target->getOwner();
        if (to_move->getType() == Type::Virus){
            download(serverport_owner,1,0);
        } else if (to_move->getType() == Type::Data){
            download(serverport_owner,0,1);
        }
        to_move->deactivate();
        b->setBoard(oldX, oldY, -1);
        return true;
    } else if (target != nullptr && target->getType() != Type::Firewall && target->getOwner() != playerincontrol) {       
        // if we are trying to move onto someone else's piece (not a firewall)
        AbstractLink* linkTarget = dynamic_cast<AbstractLink*>(whoAt(newX, newY));
        int winningID = this->battle(to_move, linkTarget);

        if (winningID == to_move->getID()){
            //cout << "initator wins" << endl;
            to_move->setX(newX);
            to_move->setY(newY);
            linkTarget->deactivate();
            to_move->reveal();
            linkTarget->reveal();
            b->setBoard(newX, newY, to_move->getID());
            b->setBoard(oldX, oldY, -1);

            // to_move wins, to_move will download targets link
            string winnerowner = to_move->getOwner();

            //download
            if (linkTarget->getType() == Type::Virus){
                download(winnerowner,1,0);
            } else if (to_move->getType() == Type::Data){
                download(winnerowner,0,1);
            }

            return true;
        } else {
            //lost the battle
            //cout << "defender wins" << endl;
            AbstractLink* linkTarget = dynamic_cast<AbstractLink*>(whoAt(newX, newY));
            to_move->deactivate();
            to_move->reveal();
            linkTarget->reveal();
            b->setBoard(oldX, oldY, -1);

            string winnerowner = linkTarget->getOwner();

            //download
            if (to_move->getType() == Type::Virus){
                download(winnerowner,1,0);
            } else if (to_move->getType() == Type::Data){
                download(winnerowner,0,1);
            }

            return true;
        }
    } else if (target != nullptr && target->getType() == Type::Firewall && target->getOwner() != playerincontrol){
      //walk onto an enemy firewall
      to_move->reveal();
      if (to_move->getType() == Type::Virus) {
        to_move->deactivate();
        download(to_move->getOwner(),1,0);
      }
      return true;
    }

    to_move->setX(newX);
    to_move->setY(newY);

    // change the internal board
    b->setBoard(newX, newY, pieces[id]->getID());
    b->setBoard(oldX, oldY, -1);

    return true;
}


int Game::appearanceToID(char c) {
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if ((*it)->getAppearance() == c){
            return (*it)->getID();
        }
    }
    return -1; // -1 if not found.
}


int Game::battle(AbstractLink* initiator, AbstractLink* defender) {
  if (initiator->getPower() >= defender->getPower()) {
    return initiator->getID();
  } else {
    return defender->getID();
  }
}

AbstractEntity* Game::whoAt(int x, int y) {
  int id = b->getValue(x, y);
  if (id == -1) {
      return nullptr;
  }
  
  return pieces[id];
}

AbstractEntity* Game::whoAt(int id){
    AbstractEntity* piece = pieces[id];
    return piece;
}

string Game::getPlayer() {
  return turn;
}

Player* Game::getFirstPlayer() {
  return p1;
}


Player* Game::getSecondPlayer() {
  return p2;
}

int Game::getVecLength(){
  return pieces.size();
}

#endif
