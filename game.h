#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "subject.h"
#include "abstractlink.h"

using namespace std;

class Game : public Subject {
  Board *b;
  string turn;
  string winner;
  Player* p1;
  Player* p2; 
  vector<AbstractEntity*> pieces;

  public:
    Game(Board* b, string turn, string winner, Player* p1, Player* p2, vector<AbstractEntity*> pieces);
    ~Game();
    Board* getBoard();
    string getWinner();
    string getTurn();
    void advance();
    
    void setWinner(string w);

    void printGameState();

    void download(string player, int virus, int data);

    void addEntityToBoard(AbstractEntity* entity);

    bool simplemove(string playerincontrol, int id, char dir);

    int appearanceToID(char c);

    int battle(AbstractLink* initiator, AbstractLink* defender);

    AbstractEntity* whoAt(int x, int y);

    AbstractEntity* whoAt(int id);

    string getPlayer();

    Player* getFirstPlayer();
    Player* getSecondPlayer();
};

#endif
