#ifndef __ABSTRACTLINK_H__
#define __ABSTRACTLINK_H__

#include <string>
#include "abstractentity.h"
using namespace std;


class AbstractLink : public AbstractEntity {
    protected:
        int power;
        bool revealed;
        bool active;
        int moveCount;

    public:
        AbstractLink(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
         bool revealed, bool active, int moveCount):
         AbstractEntity{id, x, y, appearance, type, owner}, power{power}, revealed{revealed}, active{active}, moveCount{moveCount}
         {}
        int getPower() {
            return power;
        }
        int getMoveCount() {
            return moveCount;
        }
        virtual void printLink() = 0;
        virtual ~AbstractLink() = default;
        bool isActive() {
          return active;
        }

        void reveal() {
          revealed = true;
        }

        void deactivate() {
          active = false;
        }
};


#endif