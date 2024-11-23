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
      // take in x and y.
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
      } else {
        cout << "[DEBUG] Ability::Teleport - Coordinate occupied." << endl;
      }
    }
};

class Wipe : public Ability {
  public:
    void execute(Game& game, int x, int y, char linkName) {
    }
};

#endif