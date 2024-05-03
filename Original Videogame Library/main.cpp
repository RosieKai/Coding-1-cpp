#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  srand(time(0));
    cout << "Hey! Do you like video games?\n(yes/no)\n";

    string answer = "";
    getline(cin, answer);
    
    if(answer == "no") {
        cout << "Oh... This is awkward then. I guess we don't really have anything in common... Bye.\n";
    }
    else if(answer == "yes") {
        vector<string> library;
        cout << "Hey, me too! What's your favorite game?\n";
        string game;
        getline(cin, game);
        library.push_back(game);
        cout << "Neato! I love " << game << " too!\nOh, by the way, I add that to your gaming library... Which you have... Now.\n";

        while(true) {
            cout << "What would you like to do with your video game library?\n (Show/add/delete/pick/quit)\n";
            string command;
            getline(cin, command);

            if(command == "show") {
                cout << "You have " << library.size() << " game(s) in your library.\nThey are:\n";
                for (int i = 0; i < library.size(); i++) {
                  cout << library[i] << "\n";
                }
            }
            else if(command == "add") {
                
                cout << "What game would you like to add?\n";
                
                getline(cin, game);
                    vector<string>::iterator iter = find(library.begin(), library.end(), game);
                      if (iter != library.end()) {
                         cout << "Silly, you already have that game!\n";
                      }
                    else {
                        library.push_back(game);
                        cout << "Gotcha, adding " << game << " to library.\n";
                    }
                
            }
            else if(command == "delete") {
                cout << "What game would you like to delete?\n";

                getline(cin, game);
                vector<string>::iterator iter = find(library.begin(), library.end(), game);
                  if (iter != library.end()) {
                    library.erase(iter);
                    cout << game << " is as good as gone.\n";
                }
                      else {
                          cout << "I have no clue what you're talking about.\n";
                      }
            }
            else if(command == "pick") {
                cout << "Lets pick a random game!\n";
                cout << "How about " << library[rand() % library.size()] << "?\n";
            }
            else if(command == "quit") {
                cout << "Fair enough. Catch ya on the flip side!\n";
                break;
            }
            else {
                cout << "Could you repeat that?\n";
            }
        }
        
    }
    else {
        cout << "Pfft. I don't have time for nonsense. Cya!\n";
    }
}