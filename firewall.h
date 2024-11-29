#ifndef __FIREWALL_H__
#define __FIREWALL_H__

#include <string>
#include "abstractentity.h"
#include "serverport.h"
using namespace std;


class Firewallpiece : public AbstractEntity {
    public:
        Firewallpiece(int id, size_t x, size_t y, Type type, char appearance, string owner):
         AbstractEntity{id, x, y, appearance, type, owner} {}

        Type getType() const override;

};

#endif
