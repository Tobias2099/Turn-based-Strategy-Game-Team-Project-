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
  string name;

  public:
    Ability(int id, string name) : id{id}, name{name} {}
    void execute(Game &game, int x, int y, string linkName);
    int getId() { return id; }
    string getName() { return name; }
};

#endif