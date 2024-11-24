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
        int idUnderneath;

    public:
        AbstractLink(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
         bool revealed, bool active, int moveCount, int idUnderneath):
         AbstractEntity{id, x, y, appearance, type, owner}, 
         power{power}, revealed{revealed}, active{active}, moveCount{moveCount}, idUnderneath{idUnderneath} {}
        int getPower() {
            return power;
        }
        int getMoveCount() {
            return moveCount;
        }

        virtual ~AbstractLink() = default;

        bool isActive() {
          return active;
        }

        bool isVisible() {
          return revealed;
        }

        void reveal() {
          revealed = true;
        }

        void hide() {
          revealed = false;
        }

        void deactivate() {
          active = false;
        }

        void setMoveCount(int n) {
          moveCount = n;
        }

        void setPower(int newPower) {
          power = newPower;
        }

        int getidunder() {
          return idUnderneath;
        }

        void setidunder(int id){
          idUnderneath = id;
        }
        
        void changeType() {
          if (type == Type::Data) {
            type = Type::Virus;
          } else {
            type = Type::Data;
          }
        }

        void printLink();
        
        Type getType() const override;
};


#endif