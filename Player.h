#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <string>
#include "Game.h"
#include "Ability.h"

using namespace std;

class Player{
  string name;
  int id, viruses_downloaded, data_downloaded;
  vector<Ability*> abilities;


  public:
    Player(string name, int id, int viruses_downloaded, int data_downloaded);
    int getViruses();
    int getData();
    void download(int virus, int data);
    void useAbility(int id);
};

#endif