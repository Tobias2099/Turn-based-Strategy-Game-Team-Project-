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
    vector<vector<int>> lastrep;

    public:
      Board(size_t width, size_t height);
      ~Board();

      void setBoard(int row, int col, int id);
      int getValue(int row, int col);
      int getlastValue(int row, int col);

      int getWidth();
      int getHeight();

      void snapshot();
};

#endif