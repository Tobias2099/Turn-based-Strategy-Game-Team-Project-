#include <iostream>
#include <string>
#include "game.h"

using namespace std;

int main() {
    string command;
    
    Board b{8,8};

    Player* player1 = new Player("Player 1", 0, 0, 0);
    Player* player2 = new Player("Player 2", 0, 0, 0);

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