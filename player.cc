#ifndef __PLAYER_CC__
#define __PLAYER_CC__

#include <iostream>
#include <vector>
#include "player.h"
#include "ability.h"

using namespace std;

Player::Player(string name, int id, int viruses_downloaded, int data_downloaded): 
  name{name}, viruses_downloaded{viruses_downloaded}, data_downloaded{data_downloaded}, abilities{abilities} {}

Player::~Player(){
  for (auto it = abilities.begin(); it != abilities.end(); ++it) {
    delete *it;
  }
}

int Player::getViruses(){
  return viruses_downloaded;
}
int Player::getData(){
  return data_downloaded;
}

string Player::getName(){
  return name;
}

void Player::download(int virus, int data){
  viruses_downloaded += virus;
  data_downloaded += data; 
}

bool Player::useAbility(Game& g, int id, char linkName, int x, int y) {
  //cout << "use ability number: " << id << " called " << (abilities[id])->getName() << endl;
  bool var = (abilities[id])->execute(g, x, y, linkName);
  return var;
}

void Player::addability(Ability* a) {
  abilities.emplace_back(a);
}

#endif