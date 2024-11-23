#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"

class LinkBoost : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
      //use appearanceToID and whoAt
      int linkID = game.appearanceToID(linkName);
    }
};

class Firewall : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Download : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Polarize : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Scan : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Calibrate : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Teleport : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

class Wipe : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

#endif