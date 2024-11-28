#include "displayGraphics.h"
#include "observer.h"
#include "game.h"
#include "abstractentity.h"
#include "displayText.h"

displayGraphics::displayGraphics(Game* g, int width, int height) : g{g}, width{width}, height{height}, fresh{true} {
    window = std::make_unique<Xwindow>(300, 300);
}


displayGraphics::~displayGraphics() {
   
}



void displayGraphics::notify() {
    // add drawing logic here
    if (fresh) {
        window->fillRectangle(4, 60, 178, 178, Xwindow::Black);
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++) {
                window->fillRectangle(6 + 22 * j, 62 + 22 * i, 20, 20, Xwindow::White);
            }
        }
    }

    string wkstr = "";
    string playerName = g->getPlayer();

    window->drawString(5, 10, "Player 1:");
    wkstr = "Downnloaded: " + to_string(g->getFirstPlayer()->getData()) + "D, " + to_string(g->getFirstPlayer()->getViruses()) + "V";
    window->fillRectangle(5, 12, 300, 48, Xwindow::White);
    window->drawString(5, 25,  wkstr);
    wkstr = "";
    if (g->isEnhancementsEnabled()) {
        wkstr = "Abilities: "  + to_string(g->getFirstPlayer()->abilitiesleft()) + " " + (g->getFirstPlayer())->printabvec();
    } else  {
        wkstr = "Abilities: "  + to_string(g->getFirstPlayer()->abilitiesleft()); 
    }
    window->drawString(5, 40,  wkstr);
    wkstr = "";

    const int maxLinks = 8;
    if (playerName == "Player 1"){
        for (int i = 0; i < maxLinks; i++) {
            AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i));
            wkstr = wkstr + link->getAppearance() + ": " + convertTypeToString(link->getType()) + to_string(link->getPower()) + " ";
        }
        window->drawString(5, 55,  wkstr);   
    } else {
        for (int i = 0; i < maxLinks; i++) {
            AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i));
            if (link->isVisible()) {
                wkstr = wkstr + link->getAppearance() + ": " + convertTypeToString(link->getType()) + to_string(link->getPower()) + " ";
            } else {
                wkstr = wkstr + link->getAppearance() + ": ? "; 
            }
        }
        window->drawString(5, 55,  wkstr);
    }

    for (int i = 0; i < g->getBoard()->getHeight(); i++) {
        for (int j = 0; j < g->getBoard()->getWidth(); j++)
        {   
            int oldID = g->getBoard()->getlastValue(j, i);
            int newID = g->getBoard()->getValue(j, i);
            // if there is a change,  render

            if (oldID != newID || fresh){
                // first wipe what was there
                if (!fresh){
                    window->fillRectangle(6 + 22 * j, 62 + 22 * i, 20, 20, Xwindow::White);
                }

                if (newID != -1) {
                    AbstractEntity* newentity = dynamic_cast<AbstractEntity*>(g->whoAt(newID));
                    char appc = newentity->getAppearance();
                    string app(1, appc);

                    if (newentity->getType() == Type::Data || newentity->getType() == Type::Virus) {
                        AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(newID));
                        if (!link->isVisible()){
                            window->fillRectangle(6 + (22 * j) + 3, 62 + (22 * i) + 3, 14, 14, Xwindow::Black);
                            window->fillRectangle(6 + (22 * j) + 6, 62 + (22 * i) + 4, 8, 12, Xwindow::White);
                        } else if (link->getType() == Type::Virus){
                            window->fillRectangle(6 + (22 * j) + 3, 62 + (22 * i) + 3, 14, 14, Xwindow::Red);
                            window->fillRectangle(6 + (22 * j) + 6, 62 + (22 * i) + 4, 8, 12, Xwindow::White);
                        } else if (link->getType() == Type::Data){
                            window->fillRectangle(6 + (22 * j) + 3, 62 + (22 * i) + 3, 14, 14, Xwindow::Green);
                            window->fillRectangle(6 + (22 * j) + 6, 62 + (22 * i) + 4, 8, 12, Xwindow::White);
                        }
                    } else if (newentity->getType() == Type::Serverport) {
                        window->fillRectangle(6 + (22 * j) + 3, 62 + (22 * i) + 3, 14, 14, Xwindow::Blue);
                        window->fillRectangle(6 + (22 * j) + 6, 62 + (22 * i) + 4, 8, 12, Xwindow::White);
                    } else if (newentity->getType() == Type::Firewall) {
                        window->fillRectangle(6 + (22 * j) + 3, 62 + (22 * i) + 3, 14, 14, Xwindow::Orange);
                        window->fillRectangle(6 + (22 * j) + 6, 62 + (22 * i) + 4, 8, 12, Xwindow::White);
                    }

                    window->drawString(6 + (22 * j) + 7, 62 + (22 * i) + 14, app);
                }


            }


        }
    }

    window->drawString(5, 250, "Player 2:");
    wkstr = "Downnloaded: " + to_string(g->getSecondPlayer()->getData()) + "D, " + to_string(g->getSecondPlayer()->getViruses()) + "V";
    window->fillRectangle(5, 255, 300, 50, Xwindow::White);
    window->drawString(5, 265,  wkstr);
    wkstr = "";
    if (g->isEnhancementsEnabled()) {
        wkstr = "Abilities: "  + to_string(g->getSecondPlayer()->abilitiesleft()) + " " + (g->getSecondPlayer())->printabvec();
    } else {
        wkstr = "Abilities: "  + to_string(g->getSecondPlayer()->abilitiesleft());
    }
    window->drawString(5, 280,  wkstr);
    wkstr = "";


    if (playerName == "Player 2"){
        for (int i = 0; i < maxLinks; i++) {
            AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i  + maxLinks));
            wkstr = wkstr + link->getAppearance() + ": " + convertTypeToString(link->getType()) + to_string(link->getPower()) + " ";
        }
        window->drawString(5, 295,  wkstr);   
    } else {
        for (int i = 0; i < maxLinks; i++) {
            AbstractLink* link = dynamic_cast<AbstractLink*>(g->whoAt(i  + maxLinks));
            if (link->isVisible()) {
                wkstr = wkstr + link->getAppearance() + ": " + convertTypeToString(link->getType()) + to_string(link->getPower()) + " ";
            } else {
                wkstr = wkstr + link->getAppearance() + ": ? "; 
            }
        }
        window->drawString(5, 295,  wkstr);
    }

    fresh = false;
    
}