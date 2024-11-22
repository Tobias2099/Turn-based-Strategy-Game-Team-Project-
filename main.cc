#include <iostream>
#include <string>
#include "game.h"

using namespace std;

int main() {
    string command;
    
    Board b{8,8};

    Player* player1 = new Player("Player 1", 0, 0, 0);
    Player* player2 = new Player("Player 2", 0, 0, 0);

    //player1 pieces
    AbstractEntity *player1a = new DataLink{0, 0, 0, true, 'a', "Player 1", 1};
    AbstractEntity *player1b = new DataLink{1, 0, 1, true, 'b', "Player 1", 2};
    AbstractEntity *player1c = new DataLink{2, 0, 2, true, 'c', "Player 1", 3};
    AbstractEntity *player1d = new DataLink{3, 3, 1, true, 'd', "Player 1", 4};

    AbstractEntity *player1e = new VirusLink{4, 4, 1, true, 'e', "Player 1", 1};
    AbstractEntity *player1f = new VirusLink{5, 5, 0, true, 'f', "Player 1", 2};
    AbstractEntity *player1g = new VirusLink{6, 6, 0, true, 'g', "Player 1", 3};
    AbstractEntity *player1h = new VirusLink{7, 7, 0, true, 'h', "Player 1", 4};

    //player2 pieces
    AbstractEntity *player2a = new DataLink{8, 0, 7, true, 'a', "Player 2", 1};
    AbstractEntity *player2b = new DataLink{9, 1, 7, true, 'b', "Player 2", 2};
    AbstractEntity *player2c = new DataLink{10, 2, 7, true, 'c', "Player 2", 3};
    AbstractEntity *player2d = new DataLink{11, 3, 6, true, 'd', "Player 2", 4};
    AbstractEntity *player2e = new VirusLink{12, 4, 6, true, 'e', "Player 2", 1};
    AbstractEntity *player2f = new VirusLink{13, 5, 7, true, 'f', "Player 2", 2};
    AbstractEntity *player2g = new VirusLink{14, 6, 8, true, 'g', "Player 2", 3};
    AbstractEntity *player2h = new VirusLink{15, 7, 7, true, 'h', "Player 2", 4};

    //player1 server ports
    AbstractEntity *player1s1 = new Serverport{16, 3, 0, true, 'S', "Player 1"};
    AbstractEntity *player1s2 = new Serverport{16, 4, 0, true, 'S', "Player 1"};

    //player2 server ports
    AbstractEntity *player2s1 = new Serverport{16, 3, 7, false, 'S', "Player 2"};
    AbstractEntity *player2s2 = new Serverport{16, 4, 7, false, 'S', "Player 2"};

    Game g(&b, "Player 1", "None", player1, player2);

    while (g.getWinner() == "None"){

        while (std::cin >> command) {
            if (command == "board" ) {
                g.printGameState();
            } else if (command == "move") {
                string playerincontrol = g.getTurn();
                char name;
                char dir;
                cin >> name >> dir;
                bool movestat = g.getBoard()->simplemove(playerincontrol, g.getBoard()->appearance2id(name), dir);
                if (movestat){
                    g.advance();
                    break;
                }
            } else if (command == "whoat") {
                int x, y;
                cin >> x >> y;
                if (g.getBoard()->whoat(x,y) != nullptr){
                    g.getBoard()->whoat(x, y)->printPiece();
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