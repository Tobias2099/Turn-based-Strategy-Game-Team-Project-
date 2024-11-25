#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <vector>
#include <algorithm>
#include "observer.h"
#include "game.h"

class displayText : public Observer {
  Game* g;

	public:
		displayText(Game* g);
    ~displayText();
    virtual void notify();
};

string convertTypeToString(Type type);

#endif
