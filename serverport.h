#ifndef __SERVERPORT_H__
#define __SERVERPORT_H__

#include <string>
#include "abstractentity.h"
#include "serverport.h"
using namespace std;


class Serverport : public AbstractEntity {
    public:
        Serverport(int id, size_t x, size_t y, Type type, char appearance, string owner):
         AbstractEntity{id, x, y, type, appearance, owner} {}

        Type getType() const override;

};

#endif