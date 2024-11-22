#ifndef __PLAYER_CC__
#define __PLAYER_CC__

#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

Player::Player(string name, int id, int viruses_downloaded, int data_downloaded): 
  name{name}, viruses_downloaded{viruses_downloaded}, data_downloaded{data_downloaded}, abilities{abilities} {}

int Player::getViruses(){
  return viruses_downloaded;
}
int Player::getData(){
  return data_downloaded;
}

void Player::download(int virus, int data){
  viruses_downloaded += virus;
  data_downloaded += data; 
}

void useAbility(int id) {
  cout << "use ability";
}

#endif