#ifndef __LINK_H__
#define __LINK_H__

#include <string>
#include "abstractentity.h"
using namespace std;


class Link : public AbstractEntity {
    protected:
        int power;
        bool revealed;
        bool active;
        int moveCount;
        int idUnderneath;

    public:
        Link(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
                  bool revealed, bool active, int moveCount, int idUnderneath);
        int getPower();
        int getMoveCount();
        virtual ~Link();

        bool isActive();
        bool isVisible();
        void reveal();
        void hide();
        void deactivate();
        void setMoveCount(int n);
        void setPower(int newPower);
        void changeType();

        void printLink();

        int getidunder();
        void setidunder(int id);

        Type getType() const override;
};


#endif
