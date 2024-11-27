#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <unordered_map>
#include "game.h"
#include "abstractentity.h"
#include "ability.cc"
#include "displayGraphics.h"
#include "displayText.h"
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
            g->addEntityToBoard(std::make_unique<AbstractLink>(j, x, y, c, Type::Data, player, power, false, true, 1, -1));
            available[token] = 0;
        }

        if (token[0] == 'V'){
            //add a viruslink
            g->addEntityToBoard(std::make_unique<AbstractLink>(j, x, y, c, Type::Virus, player, power, false, true, 1, -1));
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
            g->addEntityToBoard(std::make_unique<AbstractLink>(i, x, y, c, Type::Data, player, power, false, true, 1,-1));
            available[token] = 0;
        }

        if (token[0] == 'V'){
            //add a viruslink
            g->addEntityToBoard(std::make_unique<AbstractLink>(i, x, y, c, Type::Virus, player, power, false, true, 1,-1));
            available[token] = 0;
        }
        x++;
        c++;
    }
    cout << "[DEBUG] Successfully loaded links for " << player << endl;
    return true;
}

bool abstringchecker(string arg){
    const string permitted = "LFDSPCTW";
    unordered_map<char, int> allowed =
    {{'L', 0},{'F', 0},{'D', 0},{'S', 0},
    {'P', 0},{'C', 0},{'T', 0},{'W', 0}};

    //length
    if (arg.length() != 5){
        cout << "[DEBUG] Must have exactly 5 abilities!" << endl;
        return false;
    }

    for (int i = 0; i < 5; i++){
        if (allowed.find(arg[i]) == allowed.end()){
            cout << "[DEBUG] At least one ability was not permitted." << endl;
            cout << "and it was: " << arg[i] << endl;
            return false;
        }

        if (allowed[arg[i]] > 1) {
            cout << "[DEBUG] Trying to add too many copies of an ability" << endl;
            return false;
        }

        allowed[arg[i]] += 1;
    }

    return true;
}

void loadabilities(Player* player, string arg, bool check){
    //what do we do with partial or unfilled ability strings?
    //no checking for double abilities, length yet

    if (check && !abstringchecker(arg)){
        cout << "[DEBUG] Ability string for " << player->getName() 
        << " not accepted. Reverting to default." << endl;
        arg = "LFDSP";
    }

    int arglen = arg.length();
    for (int i = 0; i < arglen; i++) {
        char c = arg[i];
        switch (c) {
            case 'L':
                player->addability(std::make_unique<LinkBoost>(i, c, player->getName()));
                break;
            case 'F':
                player->addability(std::make_unique<Firewallab>(i, c, player->getName()));
                break;
            case 'D':
                player->addability(std::make_unique<Download>(i, c, player->getName()));
                break;
            case 'S':
                player->addability(std::make_unique<Scan>(i, c, player->getName()));
                break;
            case 'P':
                player->addability(std::make_unique<Polarize>(i, c, player->getName()));
                break;
            case 'T':
                player->addability(std::make_unique<Teleport>(i, c, player->getName()));
                break;
            case 'C':
                player->addability(std::make_unique<Calibrate>(i, c, player->getName()));
                break;
            case 'W':
                player->addability(std::make_unique<Wipe>(i, c, player->getName()));
                break;
            default:
                cout << "Invalid ability" << endl;
                break;
        }
    }

    cout << "[DEBUG] " << player->getName() << " will use abilities " << arg << endl;
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
    
    Board b{8,8};

    std::unique_ptr<Player> player1 = std::make_unique<Player>("Player 1", 0, 0, 0, 5);
    std::unique_ptr<Player> player2 = std::make_unique<Player>("Player 2", 0, 0, 0, 5);



    vector<std::unique_ptr<AbstractEntity>> pieces;
    Game g(&b, "Player 1", "None", player1.get(), player2.get(), std::move(pieces));

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
        cout << "[DEBUG] Player 1 requested abilities: " << options["-ability1"] << endl;
        loadabilities(player1.get(), options["-ability1"], true);
    } else {
        cout << "[DEBUG] Player 1 will use default abilities LFDSP" << endl;
        loadabilities(player1.get(), "LFDSP", false);
    }

    if (options.find("-ability2") != options.end()) {
        cout << "[DEBUG] Player 2  requested abilities: " << options["-ability2"] << endl;
        loadabilities(player2.get(), options["-ability2"], true);
    } else {
        cout << "[DEBUG] Player 2 will use default abilities LFDSP" << endl;
        loadabilities(player2.get(), "LFDSP", false);
    }

    //player1 server ports  
    g.addEntityToBoard(std::make_unique<ServerPort>(16, 3, 0, Type::Serverport, 'S', "Player 1"));
    g.addEntityToBoard(std::make_unique<ServerPort>(17, 4, 0, Type::Serverport, 'S', "Player 1"));

    //player2 server ports
    g.addEntityToBoard(std::make_unique<ServerPort>(18, 3, 7, Type::Serverport, 'S', "Player 2"));
    g.addEntityToBoard(std::make_unique<ServerPort>(19, 4, 7, Type::Serverport, 'S', "Player 2"));

    std::unique_ptr<displayGraphics> graphicsObserver = nullptr;

    if (options.find("-graphics") != options.end()) {
        cout << "[DEBUG] Graphics mode on" << endl;
        graphicsObserver = std::make_unique<displayGraphics>(&g, 300, 300);
        g.attach(graphicsObserver.get());
    }

    displayText textObserver{&g};
    g.attach(&textObserver);

    istream* inputStream = &cin;
    bool sequencemode = false;
    string seqfname = "";
    ifstream infile;

    while (g.getWinner() == "None"){

        if (sequencemode) {
            infile.open(seqfname);
            if (!infile.is_open()) {
                cout << "[DEBUG] Can't open sequence file " << seqfname 
                << " Reverting to stdin" << endl;
                sequencemode = false;
            } else {
                cout << "[DEBUG] switched to seqmode successfully." << endl;
                inputStream = &infile;
                sequencemode = false;
            }
        }

        string command;
        while (*inputStream >> command) {
            if (command == "board" ) {
                g.notifyObservers();
            } else if (command == "move") {
                string playerincontrol = g.getPlayer();
                char name;
                char dir;
                *inputStream >> name >> dir;
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
                *inputStream >> x >> y;
                if (g.whoAt(x,y) != nullptr){
                    cout << g.whoAt(x, y)->getAppearance() << endl;
                } else {
                    cout << "Nothing" << endl;
                }
            } else if (command == "quit") {
                g.setWinner("ESC");
                break;
            } else if (command == "ability") {
                bool abilitystat = true;

                int id;
                int x, y = -1;
                char linkName = '0';
                string playerincontrol = g.getPlayer();

                Player *p = nullptr;
                if (playerincontrol == "Player 1") {
                  p = g.getFirstPlayer();
                } else if (playerincontrol == "Player 2") {
                  p = g.getSecondPlayer();
                }

                *inputStream >> id;
                if (id <= 0 || id > 5) {
                  cout << "Invalid ability id." << endl;
                  continue;
                }
                

                if (p->getAbilityName(id) == 'T') { //teleport
                  if (*inputStream >> x) {
                    *inputStream >> y;
                    *inputStream >> linkName;
                  } else {
                    inputStream->clear();
                    *inputStream >> linkName;
                    *inputStream >> x;
                    *inputStream >> y;
                  }
                  
                  if (playerincontrol == "Player 1"){
                      abilitystat = player1->useAbility(g, id - 1, linkName, x, y);
                  } else {
                      abilitystat = player2->useAbility(g, id - 1, linkName, x, y);
                  }
                } else if (p->getAbilityName(id) == 'W') { //wipe
                  if (playerincontrol == "Player 1"){
                      abilitystat = player1->useAbility(g, id - 1, '0', -1, -1);
                  } else {
                      abilitystat = player2->useAbility(g, id - 1, '0', -1, -1);
                  }
                } else { 
                  if (*inputStream >> x) {
                    if (!(*inputStream >> y)) {
                      inputStream->clear();
                      inputStream->ignore();
                      cout << "Command not recognized." << endl;
                      continue;
                    }
  
                  } else{
                    inputStream->clear();
                    if (!(*inputStream >> linkName)) {
                      inputStream->clear();
                    }
                  }
                  /**inputStream >> linkName;
                  if (linkName >= '0' && linkName <= '9'){
                    x = static_cast<int>(linkName - '0');
                    *inputStream >> y;

                    //cout << "ready to use ability " << id << " with coords " << x << " " << y << endl;

                    if (playerincontrol == "Player 1"){
                        abilitystat = player1->useAbility(g, id - 1, '0', x, y);
                    } else {
                        abilitystat = player2->useAbility(g, id - 1, '0', x, y);
                    }
                  } else {
                      //cout << "ready to use ability " << id << " with linkname " << linkName << endl;
                      if (playerincontrol == "Player 1"){
                          abilitystat = player1->useAbility(g, id - 1, linkName, -1, -1);
                      } else {
                          abilitystat = player2->useAbility(g, id - 1, linkName, -1, -1);
                      }
                  }*/
                  if (playerincontrol == "Player 1"){
                    abilitystat = player1->useAbility(g, id - 1, linkName, x, y);
                  } else {
                    abilitystat = player2->useAbility(g, id - 1, linkName, x, y);
                  }
                }

                
                if (abilitystat){
                    g.notifyObservers();
                    break;
                }
                // do we want this here?
                //g.notifyObservers();

            } else if (command == "sequence") {
                *inputStream >> seqfname;
                sequencemode = true;
                cout << "[DEBUG] Attempting sequence load with filename " << seqfname << endl;
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
    //winner for when 4 viruses
}