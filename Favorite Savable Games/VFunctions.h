#include "includes.h"
#include <fstream>

vector<string> library;
string name;
string input;
string yn;
string game;
string line;

vector<string> callSave() {
    ifstream gameFile ("Save.txt");

    if(gameFile.is_open()) {
        while(getline(gameFile, line)) {
            library.push_back(line);
        }
    } else {
        cout << "Could not find save file\n";
    }
        gameFile.close();
    return library;
}

void showSave() {
    if (library.size() > 0) {
        library.size();
        cout << "You have " << library.size() << " game(s) in your library.\nThey are:\n";
        for (int i = 0; i < library.size(); i++) {
            cout << i + 1 << ") " << library[i] << "\n";
        } 
    } else {cout << "There are no games in your video game library.\n";}
}

void addGame() {
    cout << "What game would you like to add?\n";
    getline(cin, input);
    library.push_back(input);
    while (true) {
    cout << "Are you sure you want to save " << input << " to your library? (y/n)\n";
    getline(cin, yn);
    if (yn == "y") {
        ofstream gameFile ("Save.txt", ios:: app);
        if(gameFile.is_open()) {
            gameFile << input << "\n";
            cout << input << " has been added to your video game library!\n";
        } else {
            cout << "Could not find save file\n";
        }
            gameFile.close();
        break;
    } else if (yn == "n") {
        cout << "Fine. Nevermind then.\n";
        library.pop_back();
        break;
    } else {
        cout << "\nInvalid Response\n\n";
        }
    }
}

void delGame() {
    if (library.size() > 0) {
        showSave();
        cout << "Which game would you like to delete?\n";
        getline(cin, input);
        int amount = library.size();
        for (int i = 0; i < amount; i++) {
            if (library[i] == input) {
                cout << "are you sure you want to delete " << input << "? (y/n)\n";
                getline(cin, yn);
                if (yn == "y") {
                    ofstream gameFile ("Save.txt", ios:: trunc);
                    if (gameFile.is_open())
                    {
                          vector<string>::iterator iter = find(library.begin(), library.end(), input);
                            if (iter != library.end()) {
                                library.erase(iter);
                                cout << input << " is as good as gone.\n";
                                for (int i = 0; i < amount - 1; i++) {
                                    gameFile << library[i] << "\n";
                                }
                            }
                            else {
                                cout << "I have no clue what you're talking about.\n";
                            }
                        gameFile.close();
                    }
                    else {cout << "Unable to open file\n";}
                } 
                else if (yn == "n") {cout << "Fine, sheesh, nevermind.\n";} 
                else {cout << "\nInvalid Response\n";}
                break;
            } else if (i == library.size() - 1) {
                cout << "Game Not Found\n";
                }
        } 
    } else {cout << "You have no games to delete!\n";}
}

void editGame() {
    if (library.size() > 0) {
        string newGame;
        showSave();
        cout << "Which game would you like to edit?\n";
        getline(cin, input);
        for (int i = 0; i < library.size(); i++) {
            if (library[i] == input) {
                cout << "What would you like to change " << input << " to?\n";
                getline(cin, newGame);
                library[i] = newGame;
                ofstream gameFile ("Save.txt", ios:: trunc);
                if (gameFile.is_open()) {
                    for (int i = 0; i < library.size(); i++) {
                        gameFile << library[i] << "\n";  
                    }
                    gameFile.close();
                } else {cout << "Unable to open file\n";}
                cout << input << " has been changed to " << newGame << "!\n";
                break;
            } else if (i == library.size() - 1) {
                cout << "Game Not Found\n";
                }
        }
    }
    else {cout << "You have no games to edit!\n";}
}

void clearGames() {
    if (library.size() > 0) {
        cout << "Are you sure you want to wipe your video game library? (y/n)\n";
        getline(cin, input);
        if (input == "y") {
            library.clear();
            ofstream gameFile ("Save.txt", ios:: trunc);
            if (gameFile.is_open()) {
                gameFile.close();
                cout << "Your video game library has been wiped.\n";
            }
            else {cout << "Unable to open file\n";}
        }
        else if (input == "n") {cout << "Good thing I asked first!\n";}
        else {cout << "\nInvalid Response\n";}
    }
    else {cout << "You have no games to clear!\n";}
}
// ask user which game to edit*
// ask user what they want to change
// find old game in vector
// update old game in vector
// update Savt.txt