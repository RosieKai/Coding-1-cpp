#include "includes.h"
#include "VFunctions.h"

// Create a program that will accept the user's fav games.

// On quit of application, save those games to file.
// On Open, load those games from file.
// Use Getline().
// Use a Vector<string>.
// Use a header file for the load() and save() functions.
// Load will add the favgames from the .txt file to the vector. Save will write the favgames from the vector to the file.
// The user should be able to Add a favGame, Edit a favGame, Show the favGames, and Clear the list of favGames.

int main() {
    callSave();
    string answer;
    cout << "Welcome to your Video Game Library!\n";
    while(true) {
        cout << "\nWhat would you like to do?\n\n";
        cout << "1 = Show Games\n";
        cout << "2 = Add Game\n";
        cout << "3 = Edit Game\n";
        cout << "4 = Delete Game\n";
        cout << "5 = Clear Games\n";
        cout << "6 = Quit\n\n";
        getline(cin, answer);
        if (answer == "1") {showSave();}
        else if (answer == "2") {addGame();}
        else if (answer == "3") {editGame();}
        else if (answer == "4") {delGame();}
        else if (answer == "5") {clearGames();}
        else if (answer == "6") {cout << "See you later!\n";break;}
        else {cout << "Invalid Response\n";}
    }
}