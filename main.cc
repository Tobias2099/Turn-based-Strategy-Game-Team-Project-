#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <unordered_map>
#include "game.h"
#include "abstractentity.h"
#include "displayText.h"
#include "datalink.h"
#include "viruslink.h"
#include "serverport.h"
using namespace std;


void randomizeplayers(Game* g, unordered_map<string, int> available, string player, int startid, int endid, char startchar) {
    int overallcountav = 8;

    size_t x = 0;
    int j = startid;

    char c = startchar;
    for (int i = 0; i < overallcountav; i++){
        int currentcountav = 0;

        size_t y = 0;
        if (player == "Player 2"){
            y = 7;
        }

        vector<string> valid_keys;
        for (auto entry : available) {
            if (entry.second == 1) {
                currentcountav++;
                valid_keys.emplace_back(entry.first);
            }
        }

        int n = currentcountav - 1;  

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, n);
        int random_number = dis(gen);

        string token  = valid_keys[random_number];
        available[token] = 0;

        int power = static_cast<int>(token[1] - '0');

        if (x == 3 || x == 4) {
            if (player == "Player 1"){
                y += 1;
            }
            if (player == "Player 2"){
                y -= 1;
            }
        }

        if (token[0] == 'D'){
            //add a datalink
            g->addEntityToBoard(new DataLink{j, x, y, c, Type::Data, player, power, false, true, 1});
            available[token] = 0;
        }

        if (token[0] == 'V'){
            //add a viruslink
            g->addEntityToBoard(new VirusLink{j, x, y, c, Type::Virus, player, power, false, true, 1});
            available[token] = 0;
        }
        x++;
        c++;
        j++;
    }
    cout << "[DEBUG] Successfully loaded links for " << player << endl;
}


bool loadplayers(Game* g, string filename, string player, int startid, int endid, char startchar){
    unordered_map<string, int> available =
    {{"D4", 1},{"D3", 1},{"D2", 1},{"D1", 1},
    {"V4", 1},{"V3", 1},{"V2", 1},{"V1", 1}};
    ifstream f{filename};
    string token;

    if (!f.is_open()){
        if (filename != "none"){
            cout << "[DEBUG] Could not open " << filename << ". Randomizing. "<< endl;
        }
        randomizeplayers(g, available, player, startid, endid, startchar);
        return true;
    }

    size_t x = 0;
    char c = startchar;
    for (int i = startid; i <= endid; i++){
        size_t y = 0;
        if (player == "Player 2"){
            y = 7;
        }

        if (!(f >> token)) {
            cout << "[DEBUG] Could not read enough tokens from " << filename << endl;
            return false;
        }

        if (available.find(token) == available.end()) {
            cout << "[DEBUG] Token " << i << " is malformed" << endl;
            return false;
        }


        if (x == 3 || x == 4) {
            if (player == "Player 1"){
                y += 1;
            }
            if (player == "Player 2"){
                y -= 1;
            }
        }

        int power = static_cast<int>(token[1] - '0');

        if (token[0] == 'D'){
            //add a datalink
            g->addEntityToBoard(new DataLink{i, x, y, c, Type::Data, player, power, false, true, 1});
            available[token] = 0;
        }

        if (token[0] == 'V'){
            //add a viruslink
            g->addEntityToBoard(new VirusLink{i, x, y, c, Type::Virus, player, power, false, true, 1});
            available[token] = 0;
        }
        x++;
        c++;
    }
    cout << "[DEBUG] Successfully loaded links for " << player << endl;
    return true;
}

int main(int argc, char* argv[]) {
    unordered_map<string, string> options;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg[0] == '-') { 
            string option = arg;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options[option] = argv[i + 1];
                i++;
            } else {
                options[option] = "";
            }
        }
    }


    string command;
    
    Board b{8,8};

    Player* player1 = new Player("Player 1", 0, 0, 0);
    Player* player2 = new Player("Player 2", 0, 0, 0);

<<<<<<< HEAD
    //player1 pieces
    AbstractLink *player1a = new DataLink{0, 0, 0, 'a', Type::Data, "Player 1", 1, false, true, 1};
    AbstractLink *player1b = new DataLink{1, 1, 0, 'b', Type::Data, "Player 1", 2, false, true, 1};
    AbstractLink *player1c = new DataLink{2, 2, 0, 'c', Type::Data, "Player 1", 3, false, true, 1};
    AbstractLink *player1d = new DataLink{3, 3, 1, 'd', Type::Data, "Player 1", 4, false, true, 1};

    AbstractLink *player1e = new VirusLink{4, 4, 1, 'e', Type::Virus, "Player 1", 1, false, true, 1};
    AbstractLink *player1f = new VirusLink{5, 5, 0, 'f', Type::Virus, "Player 1", 2, false, true, 1};
    AbstractLink *player1g = new VirusLink{6, 6, 0, 'g', Type::Virus, "Player 1", 3, false, true, 1};
    AbstractLink *player1h = new VirusLink{7, 7, 0, 'h', Type::Virus, "Player 1", 4, false, true, 1};

    //player2 pieces
    AbstractLink* player2a = new DataLink{8, 0, 7, 'A', Type::Data, "Player 2", 1, false, true, 1};
    AbstractLink* player2b = new DataLink{9, 1, 7, 'B', Type::Data, "Player 2", 2, false, true, 1};
    AbstractLink* player2c = new DataLink{10, 2, 7, 'C', Type::Data, "Player 2", 3, false, true, 1};
    AbstractLink* player2d = new DataLink{11, 3, 6, 'D', Type::Data, "Player 2", 4, false, true, 1};

    AbstractLink* player2e = new VirusLink{12, 4, 6, 'E', Type::Virus, "Player 2", 1, false, true, 1};
    AbstractLink* player2f = new VirusLink{13, 5, 7, 'F', Type::Virus, "Player 2", 2, false, true, 1};
    AbstractLink* player2g = new VirusLink{14, 6, 7, 'G', Type::Virus, "Player 2", 3, false, true, 1};
    AbstractLink* player2h = new VirusLink{15, 7, 7, 'H', Type::Virus, "Player 2", 4, false, true, 1};
    //AbstractLink{id, x, y, appearance, type, owner, power, revealed, active, moveCount} {}

    //player1 server ports  
    AbstractEntity* player1s1 = new ServerPort{16, 3, 0, Type::Serverport, 'S', "Player 1"};
    AbstractEntity* player1s2 = new ServerPort{16, 4, 0, Type::Serverport, 'S', "Player 1"};

    //player2 server ports
    AbstractEntity* player2s1 = new ServerPort{16, 3, 7, Type::Serverport, 'S', "Player 2"};
    AbstractEntity* player2s2 = new ServerPort{16, 4, 7, Type::Serverport, 'S', "Player 2"};

=======
>>>>>>> b03bb27b23e72d5ae0831dbee6277c4a7e3d929a
    vector<AbstractEntity*> pieces;
    Game g(&b, "Player 1", "None", player1, player2, pieces);

    cout << "[DEBUG] all arguments: " << endl;
    for (auto entry : options) {
        cout << entry.first << ": " << entry.second << endl;
    }

    if (options.find("-link1") != options.end()) {
        cout << "[DEBUG] Attempting to load links from " << options["-link1"] << endl;
        if (!loadplayers(&g, options["-link1"], "Player 1", 0, 7, 'a')){
            cout << "[DEBUG] Something went wrong. Must restart." << endl;
            return 1;
        }
    } else {
        cout << "[DEBUG] No link1 file supplied. Randomising." << endl;
        loadplayers(&g, "none", "Player 1", 0, 7, 'a');
    }

    if (options.find("-link2") != options.end()) {
        cout << "[DEBUG] Attempting to load links from " << options["-link2"] << endl;
        if (!loadplayers(&g, options["-link2"], "Player 2", 8, 15, 'A')){
            cout << "[DEBUG] Something went wrong. Must restart." << endl;
            return 1;
        }
    } else {
        cout << "[DEBUG] No link2 file supplied. Randomising." << endl;
        loadplayers(&g, "none", "Player 2", 8, 15, 'A');
    }

    if (options.find("-ability1") != options.end()) {
        cout << "[DEBUG] player1 abilities: " << options["-ability1"] << endl;
    } else {
        cout << "[DEBUG] Warning: player 1 has not selected any abilities!" << endl;
    }

    if (options.find("-ability2") != options.end()) {
        cout << "[DEBUG] player2 abilities: " << options["-ability2"] << endl;
    } else {
        cout << "[DEBUG] Warning: player 2 has not selected any abilities!" << endl;
    }

    if (options.find("-graphics") != options.end()) {
        cout << "[DEBUG] Graphics mode on" << endl;
    }

    //player1 server ports  
    g.addEntityToBoard(new ServerPort{16, 3, 0, Type::Serverport, 'S', "Player 1"});
    g.addEntityToBoard(new ServerPort{16, 4, 0, Type::Serverport, 'S', "Player 1"});

    //player2 server ports
    g.addEntityToBoard(new ServerPort{16, 3, 7, Type::Serverport, 'S', "Player 2"});
    g.addEntityToBoard(new ServerPort{16, 4, 7, Type::Serverport, 'S', "Player 2"});

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
                bool movestat = g.simplemove(playerincontrol, g.appearanceToID(name), dir, -1);
                if (movestat){
                    //why observers?
                    g.advance();
                    g.notifyObservers();
                    break;
                }
                // do we want this here?
                //g.notifyObservers();
            } else if (command == "whoat") {
                int x, y;
                cin >> x >> y;
                if (g.whoAt(x,y) != nullptr){
                    g.whoAt(x, y)->getAppearance();
                } else {
                    cout << "Nothing" << endl;
                }
            } else if (command == "quit") {
                g.setWinner("ESC");
                break;
            } else {
                cout << "Command not recognized." << endl;
                continue;
            }
        } 
    }
    if (g.getWinner() == "Player 1" || g.getWinner() == "Player 2"){
        cout << g.getWinner() << " has won the game!" << endl;
    }
}