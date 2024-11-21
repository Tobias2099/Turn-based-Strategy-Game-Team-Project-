#ifndef __ABILITY_H__
#define __ABILITY_H__

#include <iostream>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

class Ability{
  int id;  
  string name;

  public:
    Ability(int id, string name);
    void execute(Board& board, int x, int y, string linkName);
};

#endif