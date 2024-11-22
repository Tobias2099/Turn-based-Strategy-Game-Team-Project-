#ifndef __SERVERPORT_H__
#define __SERVERPORT_H__

#include <string>
#include "abstractentity.h"
#include "serverport.h"
using namespace std;


class ServerPort : public AbstractEntity {
    public:
        ServerPort(int id, size_t x, size_t y, Type type, char appearance, string owner):
         AbstractEntity{id, x, y, appearance, type, owner} {}

        Type getType() const override;

};

#endif