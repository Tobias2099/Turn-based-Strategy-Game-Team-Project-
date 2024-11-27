#ifndef __PLAYER_CC__
#define __PLAYER_CC__

#include <iostream>
#include <vector>
#include <memory>
#include "player.h"
#include "ability.h"

using namespace std;

Player::Player(string name, int id, int viruses_downloaded, int data_downloaded, int ableft): 
  name{name}, viruses_downloaded{viruses_downloaded}, 
  data_downloaded{data_downloaded}, ableft{ableft}
  {}

Player::~Player(){
  // for (auto it = abilities.begin(); it != abilities.end(); ++it) {
  //   delete *it;
  // }
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
  if (ableft == 0) {
    cout << "[DEBUG] No abilities left!" << endl;
    return false;
  }

  if ((abilities[id])->hasbeenused()){
    cout << "[DEBUG] Already used this ability!" << endl;
    return false;
  }
  bool var = (abilities[id])->execute(g, x, y, linkName);
  ableft -= 1;
  return var;

}

void Player::addability(std::unique_ptr<Ability> ability) {
  abilities.emplace_back(std::move(ability));
}

int Player::abilitiesleft() {
  return ableft;
}

string Player::printabvec() {
  string vec = "[";
  for (size_t i = 0; i < abilities.size(); i++){
    if (abilities[i]->hasbeenused()){
      vec += "~";
    } else {
      vec += abilities[i]->getName();
    }
  }
  vec += "]";
  return vec;
}

char Player::getAbilityName(int id) {
  return abilities[id - 1]->getName();
}

#endif