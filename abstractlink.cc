#ifndef __ABSTRACTLINK_CC__
#define __ABSTRACTLINK_CC__

#include <string>
#include "abstractlink.h"
#include <iostream>
using namespace std;

#include "abstractlink.h"

AbstractLink::AbstractLink(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
                           bool revealed, bool active, int moveCount)
    : AbstractEntity{id, x, y, appearance, type, owner}, power{power}, revealed{revealed}, active{active}, moveCount{moveCount} {}

AbstractLink::~AbstractLink() = default;

int AbstractLink::getPower() {
    return power;
}

int AbstractLink::getMoveCount() {
    return moveCount;
}

bool AbstractLink::isActive() {
    return active;
}

bool AbstractLink::isVisible() {
    return revealed;
}

void AbstractLink::reveal() {
    revealed = true;
}

void AbstractLink::hide() {
    revealed = false;
}

void AbstractLink::deactivate() {
    active = false;
}

void AbstractLink::setMoveCount(int n) {
    moveCount = n;
}

void AbstractLink::setPower(int newPower) {
    power = newPower;
}

void AbstractLink::changeType() {
    if (type == Type::Data) {
        type = Type::Virus;
    } else {
        type = Type::Data;
    }
}


Type AbstractLink::getType() const {
    return type;
}


void AbstractLink::printLink() {
    cout << "At [" << x << "," << y << "]: " << "Name: " 
    << appearance << " | Type: " << this->getType() << " | Owner: " << owner << endl;
}

#endif