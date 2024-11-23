#ifndef __FIREWALL_CC__
#define __FIREWALL_CC__

#include <string>
#include <iostream>
#include "firewall.h"
using namespace std;


Type Firewallpiece::getType() const {
    return Type::Firewall;
}

#endif