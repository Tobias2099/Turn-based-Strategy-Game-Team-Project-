#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include "memory.h"
#include "board.h"
#include "player.h"
#include "subject.h"
#include "link.h"

class Player;

using namespace std;

class Game : public Subject {
  Board *b;
  string turn;
  string winner;
  Player *p1;
  Player *p2;
  vector<std::unique_ptr<AbstractEntity>> pieces;
  bool enhancements;

  public:
    Game(Board* b, string turn, string winner, Player* p1, Player* p2, vector<std::unique_ptr<AbstractEntity>> pieces);
    ~Game();
    Board* getBoard();
    string getWinner();
    string getTurn();
    bool isEnhancementsEnabled();
    void setEnhancements(bool enhancements);
    vector<AbstractEntity*> getPieces();

    vector<AbstractEntity*>& getPiecesRef();
    
    void advance();
    
    void setWinner(string w);

    void printGameState();

    void download(string player, int virus, int data);

    void addEntityToBoard(std::unique_ptr<AbstractEntity> entity);

    bool simplemove(string playerincontrol, int id, char dir, int steps);

    int appearanceToID(char c);

    int battle(Link* initiator, Link* defender);

    AbstractEntity* whoAt(int x, int y);

    AbstractEntity* whoAt(int id);

    AbstractEntity* getEntity(char name);

    string getPlayer();

    Player* getFirstPlayer();
    Player* getSecondPlayer();

    int getVecLength();
};

#endif
