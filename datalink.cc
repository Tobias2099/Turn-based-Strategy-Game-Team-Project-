#ifndef __DATALINK_CC__
#define __DATALINK_CC__

#include <string>
#include <iostream>
#include "datalink.h"
using namespace std;


Type DataLink::getType() const {
    return Type::Data;
}

void DataLink::printLink() {
    cout << "At [" << x << "," << y << "]: " << "Name: " 
    << appearance << " | Type: " << this->getType() << " | Owner: " << owner << endl;
}

#endif