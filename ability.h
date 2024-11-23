#ifndef __ABILITY_H__
#define __ABILITY_H__

#include <iostream>
#include <vector>
#include <string>
#include "game.h"

class Game;

using namespace std;

class Ability {
  int id;
  char name;

  public:
    Ability(int id, char name) : id{id}, name{name} {}
    bool execute(Game &game, int x, int y, char linkName);
    int getId() { return id; }
    char getName() { return name; }
};

#endif