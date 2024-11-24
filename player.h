#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <string>
#include "game.h"
#include "ability.h"

using namespace std;

class Ability;
class Game;

class Player{
  string name;
  int id;
  int viruses_downloaded, data_downloaded;
  vector<Ability*> abilities;


  public:
    Player(string name, int id, int viruses_downloaded, int data_downloaded);
    ~Player();
    int getViruses();
    int getData();
    string getName();
    void download(int virus, int data);
    bool useAbility(Game &g, int id, char linkName, int x, int y);
    void addability(Ability* a);
};

#endif