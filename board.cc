#ifndef __BOARD_CC__
#define __BOARD_CC__

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "abstractentity.h"
#include "game.h"
#include "viruslink.h"
#include "datalink.h"
#include "serverport.h"
#include "abstractlink.h"

Board::Board(size_t width, size_t height): width{width}, height{height}, 
    boardrep{height, vector<int>(width, -1)} {}


void Board::setBoard(int row, int col, int id) {
    boardrep[row][col] = id;
}

int Board::getValue(int row, int col) {
    return boardrep[row][col];
}

int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}

Board::~Board() {
    
}

#endif