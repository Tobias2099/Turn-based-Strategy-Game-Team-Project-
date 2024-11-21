#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include "abstractentity.h"

using namespace std;

class Board{
    size_t width;
    size_t height;
    vector<vector<int>> boardrep;
    vector<AbstractEntity*> pieces;

    public:
      Board(size_t width, size_t height);
      ~Board();
      void addthing2board(Piece* bt);

      int appearance2id(char c);
      bool simplemove(string playerincontrol, int id, char dir);
      Piece* whoat(int x, int y);
      Piece* whoat(int id);
};

//int battle(Piece* initiator, Piece* defender);

#endif