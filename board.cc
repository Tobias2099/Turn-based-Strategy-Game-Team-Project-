#ifndef __BOARD_CC__
#define __BOARD_CC__

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "abstractentity.h"
#include "game.h"
#include "serverport.h"
#include "link.h"

Board::Board(size_t width, size_t height): width{width}, height{height}, 
    boardrep{height, vector<int>(width, -1)}, lastrep{height, vector<int>(width, -1)} {}


void Board::setBoard(int row, int col, int id) {
    boardrep[row][col] = id;
}

int Board::getValue(int row, int col) {
    return boardrep[row][col];
}

int Board::getlastValue(int row, int col) {
    return lastrep[row][col];
}

int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}

Board::~Board() {   
}

void Board::snapshot(){
  lastrep.assign(boardrep.begin(), boardrep.end());
}

#endif
