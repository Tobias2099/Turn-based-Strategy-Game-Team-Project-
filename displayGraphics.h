#ifndef DISPLAYGRAPHICS_H
#define DISPLAYGRAPHICS_H

#include <vector>
#include <algorithm>
#include <memory>
#include "observer.h"
#include "game.h"
#include "window.h"


class displayGraphics : public Observer {
    Game* g;
    std::unique_ptr<Xwindow> window;
    int width;
    int height;
    bool fresh;
	public:
        displayGraphics(Game* g, int width, int height);
        ~displayGraphics();
        virtual void notify();
};

#endif
