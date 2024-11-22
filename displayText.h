#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <vector>
#include <algorithm>
#include "observer.h"
#include "board.h"
#include "player.h"

class displayText : public Observer {
  Board* b;
  string playerName;

	public:
		displayText(Board* b, string playerName);
    ~displayText();
};

#endif
