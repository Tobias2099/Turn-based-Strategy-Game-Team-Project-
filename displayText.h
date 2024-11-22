#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <vector>
#include <algorithm>
#include "observer.h"
#include "game.h"

class displayText : public Observer {
  Game* g;
  string playerName;

	public:
		displayText(Game* g, string playerName);
    ~displayText();
    virtual void notify();
};

#endif
