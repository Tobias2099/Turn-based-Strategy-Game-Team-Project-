#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "abstractentity.h"
#include "displayText.h"
#include "datalink.h"
#include "viruslink.h"
#include "serverport.h"
using namespace std;



int main() {
    string command;
    
    Board b{8,8};

    Player* player1 = new Player("Player 1", 0, 0, 0);
    Player* player2 = new Player("Player 2", 0, 0, 0);

    //player1 pieces
    AbstractLink *player1a = new DataLink{0, 0, 0, 'a', Type::Data, "Player 1", 1, false, true, 1};
    AbstractLink *player1b = new DataLink{1, 0, 1, 'b', Type::Data, "Player 1", 2, false, true, 1};
    AbstractLink *player1c = new DataLink{2, 0, 2, 'c', Type::Data, "Player 1", 3, false, true, 1};
    AbstractLink *player1d = new DataLink{3, 3, 1, 'd', Type::Data, "Player 1", 4, false, true, 1};

    AbstractLink *player1e = new VirusLink{4, 4, 1, 'e', Type::Virus, "Player 1", 1, false, true, 1};
    AbstractLink *player1f = new VirusLink{5, 5, 0, 'f', Type::Virus, "Player 1", 2, false, true, 1};
    AbstractLink *player1g = new VirusLink{6, 6, 0, 'g', Type::Virus, "Player 1", 3, false, true, 1};
    AbstractLink *player1h = new VirusLink{7, 7, 0, 'h', Type::Virus, "Player 1", 4, false, true, 1};

    //player2 pieces
    AbstractLink* player2a = new DataLink{8, 0, 7, 'a', Type::Data, "Player 2", 1, true, false, 1};
    AbstractLink* player2b = new DataLink{9, 1, 7, 'b', Type::Data, "Player 2", 2, true, false, 1};
    AbstractLink* player2c = new DataLink{10, 2, 7, 'c', Type::Data, "Player 2", 3, true, false, 1};
    AbstractLink* player2d = new DataLink{11, 3, 6, 'd', Type::Data, "Player 2", 4, true, false, 1};

    AbstractLink* player2e = new VirusLink{12, 4, 6, 'e', Type::Virus, "Player 2", 1, true, false, 1};
    AbstractLink* player2f = new VirusLink{13, 5, 7, 'f', Type::Virus, "Player 2", 2, true, false, 1};
    AbstractLink* player2g = new VirusLink{14, 6, 8, 'g', Type::Virus, "Player 2", 3, true, false, 1};
    AbstractLink* player2h = new VirusLink{15, 7, 7, 'h', Type::Virus, "Player 2", 4, true, false, 1};
    //AbstractLink{id, x, y, appearance, type, owner, power, revealed, active, moveCount} {}

    //player1 server ports  
    AbstractEntity* player1s1 = new Serverport{16, 3, 0, Type::Serverport, 'S', "Player 1"};
    AbstractEntity* player1s2 = new Serverport{16, 3, 0, Type::Serverport, 'S', "Player 1"};

    //player2 server ports
    AbstractEntity* player2s1 = new Serverport{16, 3, 7, Type::Serverport, 'S', "Player 2"};
    AbstractEntity* player2s2 = new Serverport{16, 4, 7, Type::Serverport, 'S', "Player 2"};

    vector<AbstractEntity*> pieces;
    Game g(&b, "Player 1", "None", player1, player2, pieces);

    g.addEntityToBoard(player1a);
    g.addEntityToBoard(player1b);
    g.addEntityToBoard(player1c);
    g.addEntityToBoard(player1d);
    g.addEntityToBoard(player1e);
    g.addEntityToBoard(player1f);
    g.addEntityToBoard(player1g);
    g.addEntityToBoard(player1h);
    g.addEntityToBoard(player2a);
    g.addEntityToBoard(player2b);
    g.addEntityToBoard(player2c);
    g.addEntityToBoard(player2d);
    g.addEntityToBoard(player2e);
    g.addEntityToBoard(player2f);
    g.addEntityToBoard(player2g);
    g.addEntityToBoard(player2h);
    g.addEntityToBoard(player1s1);
    g.addEntityToBoard(player1s2);
    g.addEntityToBoard(player2s1);
    g.addEntityToBoard(player2s2);

    displayText textObserver{&g};
    g.attach(&textObserver);

    while (g.getWinner() == "None"){

        while (std::cin >> command) {
            if (command == "board" ) {
                g.notifyObservers();
            } else if (command == "move") {
                string playerincontrol = g.getPlayer();
                char name;
                char dir;
                cin >> name >> dir;
                bool movestat = g.simplemove(playerincontrol, g.appearanceToID(name), dir);
                if (movestat){
                    g.advance();
                    break;
                }
            } else if (command == "whoat") {
                int x, y;
                cin >> x >> y;
                if (g.whoAt(x,y) != nullptr){
                    g.whoAt(x, y)->getAppearance();
                } else {
                    cout << "Nothing" << endl;
                }
            } else {
                g.setWinner("ESC");
                break;
            }
        } 
    }
    if (g.getWinner() == "Player 1" || g.getWinner() == "Player 2"){
        cout << g.getWinner() << " has won the game!" << endl;
    }
}