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
  protected:
    string owner;
    bool used;

  public:
    Ability(int id, char name, string owner): id{id}, name{name}, owner{owner}, used{false} {}
    virtual ~Ability() = default;
    virtual bool execute(Game& game, int x, int y, char linkName) = 0;
    int getId() { return id; }
    char getName() { return name; }
    bool hasbeenused() { return used; }
};

#endif
