#ifndef __VIRUSLINK_CC__
#define __VIRUSLINK_CC__

#include <string>
#include <iostream>
#include "viruslink.h"
using namespace std;


Type VirusLink::getType() const {
    return Type::Virus;
}

void VirusLink::printLink() {
    cout << "At [" << x << "," << y << "]: " << "Name: " 
    << appearance << " | Type: " << this->getType() << " | Owner: " << owner << endl;
}

#endif