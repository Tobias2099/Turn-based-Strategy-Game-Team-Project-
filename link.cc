#ifndef __LINK_CC__
#define __LINK_CC__

#include <string>
#include "link.h"
#include <iostream>
using namespace std;

Link::Link(int id, size_t x, size_t y, char appearance, Type type, string owner, int power,
                           bool revealed, bool active, int moveCount, int idUnderneath)
    : AbstractEntity{id, x, y, appearance, type, owner}, power{power}, revealed{revealed}, active{active}, moveCount{moveCount}, idUnderneath{idUnderneath} {}

Link::~Link() = default;

int Link::getPower() {
    return power;
}

int Link::getMoveCount() {
    return moveCount;
}

bool Link::isActive() {
    return active;
}

bool Link::isVisible() {
    return revealed;
}

void Link::reveal() {
    revealed = true;
}

void Link::hide() {
    revealed = false;
}

void Link::deactivate() {
    active = false;
}

void Link::setMoveCount(int n) {
    moveCount = n;
}

void Link::setPower(int newPower) {
    power = newPower;
}

void Link::changeType() {
    if (type == Type::Data) {
        type = Type::Virus;
    } else {
        type = Type::Data;
    }
}


Type Link::getType() const {
    return type;
}


int Link::getidunder() {
    return idUnderneath;
}


void Link::setidunder(int id){
    idUnderneath = id;
}

void Link::printLink() {
    cout << "At [" << x << "," << y << "]: " << "Name: " 
    << appearance << " | Type: " << this->getType() << " | Owner: " << owner << endl;
}

#endif
