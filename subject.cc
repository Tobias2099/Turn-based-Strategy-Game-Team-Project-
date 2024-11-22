#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

void Subject::detach( Observer* o ) {
   for(auto observer = observers.begin(); observer!=observers.end(); observer++) {
    if (*observer == o) {
        delete *observer;
        observers.erase(observer);
        return;
     }
   }
}

void Subject::notifyObservers() {
    for (auto o: observers) {
        o->notify();
    }
}

