#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <vector>
#include <algorithm>
#include "observer.h"
#include "board.h"

class displayText : public Observer {
  Board *b;
	public:
		virtual void notify() = 0;
		virtual ~Observer() {}
};

#endif
