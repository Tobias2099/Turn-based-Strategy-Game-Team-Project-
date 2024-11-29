#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "game.h"
#include "ability.h"

using namespace std;

class Ability;
class Game;

class Player{
  string name;
  int id;
  int viruses_downloaded, data_downloaded, ableft;
  bool abilityAvailable;
  vector<std::unique_ptr<Ability>> abilities;


  public:
    Player(string name, int id, int viruses_downloaded, int data_downloaded, int ableft);
    ~Player();
    int getViruses();
    int getData();
    string getName();
    void download(int virus, int data);
    bool useAbility(Game &g, int id, char linkName, int x, int y);
    void addability(std::unique_ptr<Ability> ability);
    int abilitiesleft();
    string printabvec();
    char getAbilityName(int id);
    void doneTurn();
};

#endif
