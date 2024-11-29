#ifndef __SERVERPORT_CC__
#define __SERVERPORT_CC__

#include <string>
#include <iostream>
#include "serverport.h"
using namespace std;


Type ServerPort::getType() const {
    return Type::Serverport;
}

#endif
