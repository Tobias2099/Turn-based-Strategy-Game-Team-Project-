#ifndef __ABILITY_H__
#define __ABILITY_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ability{
  int id;  
  string name;

  public:
    Ability(int id, string name);
    void execute()
};

#endif