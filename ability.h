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
  string owner;

  public:
    Ability(int id, char name, string owner): id{id}, name{name}, owner{owner} {}
    void execute(Game &game, int x, int y, char linkName);
    int getId() { return id; }
    char getName() { return name; }
};

#endif