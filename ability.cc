#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include "ability.h"
#include "game.h"
#include "firewall.h"

class LinkBoost : public Ability {
  public:
    LinkBoost(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)));
      if (!link->isActive()) return false;
      if ((('a' <= linkName && linkName <= 'h') && owner != "Player 1") ||
          (('A' <= linkName && linkName <= 'H') && owner != "Player 2") ||
          !(('a' <= linkName && linkName <= 'h') || ('A' <= linkName && linkName <= 'H'))) {
          return false;
      }
    

      link->setMoveCount(link->getMoveCount() + 1);
      return true;
    }
};

class Firewallab : public Ability {
  public:
    Firewallab(int id, char name, string owner): Ability(id, name, owner) {}
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
      int id = veclength;
      game.addEntityToBoard(new Firewallpiece(id, x, y, Type::Firewall, app, owner));
      return true;
    }
};

class Download : public Ability {
  public:
    Download(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
      if (('a' <= linkName && linkName <= 'h') && owner == "Player 1") return false;
      if (('A' <= linkName && linkName <= 'H') && owner == "Player 2") return false;
      if (!((linkName >= 'a' && linkName <= 'h') || (linkName >= 'A' && linkName <= 'H'))) return false;
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.whoAt(game.appearanceToID(linkName)));

      if (link->getOwner() == owner) return false;
      if (!link->isActive()) return false;

      if (link->getType() == Type::Data) {
        game.download(owner, 0, 1);
      } else if (link->getType() == Type::Virus) {
        game.download(owner, 1, 0);
      } else {
        return false;
      }

      game.getBoard()->setBoard(link->getX(), link->getY(), -1);
      link->deactivate();
      link->hide();
      
      return true;
    }
};

class Polarize : public Ability {
  public:
    Polarize(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
      if (!((linkName >= 'a' && linkName <= 'A') || (linkName >= 'A' && linkName <= 'H'))) return false;
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.getEntity(linkName));
      if (!link->isActive()) return false;
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
    Scan(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
      if (('a' <= linkName && linkName <= 'h') && owner == "Player 1") return false;
      if (('A' <= linkName && linkName <= 'H') && owner == "Player 2") return false;
      if (!((linkName >= 'a' && linkName <= 'A') || (linkName >= 'A' && linkName <= 'H'))) return false;
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.getEntity(linkName));
      if (!link->isActive()) return false;
      if (link->getOwner() == owner) return false;
      link->reveal();
      return true;
    }
};

class Calibrate : public Ability {
  public:
    Calibrate(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
      const int maxPower = 4;
      if (!((linkName >= 'a' && linkName <= 'A') || (linkName >= 'A' && linkName <= 'H'))) return false;
      AbstractLink* link = dynamic_cast<AbstractLink*>(game.getEntity(linkName));
      if (!link->isActive()) return false;
      link->setPower(maxPower);
      return true;
    }
};

class Teleport : public Ability {
  public:
    Teleport(int id, char name, string owner): Ability(id, name, owner) {}
    bool execute(Game& game, int x, int y, char linkName) {
     //vector<AbstractEntity*> pieces = game.getPieces();
     //AbstractLink* link = nullptr;
     std::pair<int, int> coordinates;
     AbstractLink* link = dynamic_cast<AbstractLink*>(game.getEntity(linkName));
     if (!link->isActive()) return false;
     coordinates.first = link->getX();
     coordinates.second = link->getY();
      /*for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if ((*it)->getAppearance() == linkName){
            link = dynamic_cast<AbstractLink*>(*it);
            coordinates.first = link->getX();
            coordinates.second = link->getY();
            break;
        }
      }*/
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
    Wipe(int id, char name, string owner): Ability(id, name, owner) {}
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