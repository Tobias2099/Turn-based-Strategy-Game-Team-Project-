
#ifndef __DATALINK_H__
#define __DATALINK_H__

#include <string>
#include "abstractlink.h"
using namespace std;


class DataLink : public AbstractLink {
    
    public:
        DataLink(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
         bool revealed, bool active, int moveCount): 
        AbstractLink{id, x, y, appearance, type, owner, power, revealed, active, moveCount} {}

        Type getType() const override;
        void printLink() override;

};

#endif