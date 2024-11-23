#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"
#include "firewall.h"

class LinkBoost : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      //use appearanceToID and whoAt
      int linkID = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)))->setMoveCount(2);
    }
};

class Firewall : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      char app = 'x';
      if (owner == "Player 1") {
        app = 'm';
      } else {
        app = 'w';
      }

      int veclength = game.getVecLength();
      int id = veclength - 1;
      game.addEntityToBoard(new Firewallpiece(id, x, y, Type::Firewall, app, owner));
    }
};

class Download : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {

    }
};

class Polarize : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)));
    }
};

class Scan : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
    }
};

class Calibrate : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
    }
};

class Teleport : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
    }
};

class Wipe : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
    }
};

#endif