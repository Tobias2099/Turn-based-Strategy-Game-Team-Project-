#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"
#include "firewall.h"

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
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(x, y));

      if (link->getOwner() == owner) return false;

      if (link->getType() == Type::Data) {
        game.download(owner, 0, 1);
      } else if (link->getType() == Type::Virus) {
        game.download(owner, 1, 0);
      } else {
        return false;
      }

      link->deactivate();
      
      return true;
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
     vector<AbstractEntity*> pieces = game.getPieces();
     AbstractLink* link = nullptr;
     std::pair<int, int> coordinates;
      for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if ((*it)->getAppearance() == linkName){
            link = dynamic_cast<AbstractLink*>(*it);
            coordinates.first = link->getX();
            coordinates.second = link->getY();
            break;
        }
      }
      AbstractEntity* moveTo = game.whoAt(x, y);
      if (moveTo == nullptr) {
        game.getBoard()->setBoard(coordinates.first, coordinates.second, -1);
        link->setX(x);
        link->setY(y);
        return true;
      } else {
        cout << "[DEBUG] Ability::Teleport - Coordinate occupied." << endl;
        return false;
      }
    }
};

class Wipe : public Ability {
  public:
    bool execute(Game& game, int x, int y, char linkName) {
      vector<AbstractEntity*> pieces = game.getPieces();

        for (auto it = pieces.begin(); it != pieces.end(); ++it) {

          if ((*it)->getOwner() == owner && (*it)->getType() != Type::Firewall) {
              AbstractLink* linkToHide = dynamic_cast<AbstractLink*>(*it);
              if (linkToHide) linkToHide->hide();
          }
        }
        return true;
    }
};

#endif