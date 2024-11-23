#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"
#include "firewall.h"

class LinkBoost : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      //use appearanceToID and whoAt
      if (('a' <= linkName && linkName <= 'h') && owner != "Player 1") return false;
      if (('A' <= linkName && linkName <= 'H') && owner != "Player 2") return false;
      int linkID = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)))->setMoveCount(2);
      return true;
    }
};

class Firewall : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {

      if (game.whoAt(x,y) != nullptr) {
        //the target square isn't empty
        return false;
      }

      char app = 'x';
      if (owner == "Player 1") {
        app = 'm';
      } else {
        app = 'w';
      }

      int veclength = game.getVecLength();
      int id = veclength - 1;
      game.addEntityToBoard(new Firewallpiece(id, x, y, Type::Firewall, app, owner));
      return true;
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
      AbstractEntity* link = game.whoAt(game.appearanceToID(linkName));
      //may need to do dynamic cast
      if (link->getType() == Type::Data) {
        
      }
      
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