#include "displayGraphics.h"
#include "observer.h"
#include "game.h"
#include "abstractentity.h"

displayGraphics::displayGraphics(Game* g, int width, int height) : g{g}, width{width}, height{height} {
    window = std::make_unique<Xwindow>(300, 300);

}


displayGraphics::~displayGraphics() {
   
}


void displayGraphics::notify() {
    // add drawing logic here

    // sample
    window->fillRectangle(50, 50, 100, 100, Xwindow::Black);
}