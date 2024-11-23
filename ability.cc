#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"

class LinkBoost : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
      //use appearanceToID and whoAt
    }
};

class Firewall : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Download : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Polarize : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Scan : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Calibrate : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Teleport : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

class Wipe : public Ability {
  public:
    void execute(Game& game, int x, int y, string linkName) {
    }
};

#endif