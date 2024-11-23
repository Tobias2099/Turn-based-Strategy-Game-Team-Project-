#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"

class LinkBoost : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      if (('a' <= linkName && linkName <= 'h') && owner != "Player 1") return false;
      if (('A' <= linkName && linkName <= 'H') && owner != "Player 2") return false;
      int linkID = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)))->setMoveCount(2);
      return true;
    }
};

class Firewall : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {

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
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)));
      if (link->getType() == Type::Data) {
        link->setType(Type::Virus);
      } else if (link->getType() == Type::Virus) {
        link->setType(Type::Data);
      } else {
        return false;
      }
      return true;
    }
};

class Scan : public Ability { //takes coordinates as input
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(x, y));
      if (link->getOwner() == owner) return false;
      link->reveal();
      return true;
    }
};

class Calibrate : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      const int maxPower = 4;
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(x, y));
      link->setPower(maxPower);
      return true;
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