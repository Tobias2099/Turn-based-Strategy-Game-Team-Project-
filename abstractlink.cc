#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include <string>
#include "abstractlink.h"
#include <iostream>
using namespace std;


Type AbstractLink::getType() const {
    return type;
}


void AbstractLink::printLink() {
    cout << "At [" << x << "," << y << "]: " << "Name: " 
    << appearance << " | Type: " << this->getType() << " | Owner: " << owner << endl;
}

#endif