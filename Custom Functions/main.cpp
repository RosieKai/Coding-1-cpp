#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// global variables go at the top so that all functions can see the variables.
// dangerous because anyone can see and edit them.
// vector<string> colors = {"Red", "Green", "Blue", "Purple"};

// create a function named triple, that returns an int that has been tripled.
int Triple(int Number) {
    return Number * 3;
}
// variable scope - variables only exist in the code block they are created in.
void DisplayVec(vector<string> vec) {
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ".\n";
    }
}

//function named "addtovec" return type is void, accepts two parameters,
// a vector of strings, and a string to add.
vector<string> AddToVec(vector<string> vec, string newItem) {
    vec.push_back(newItem);
    return vec;
}

// pass by copy/value, versus passing by reference
// passing by
// adding an & makes it a reference rather than a copy
// Reminder: while loops check condition before running the function
// Do while loops check condition after running the function
// do while loops are good for if you need to ask for player input at least once
void RefAddToVector(vector<string>& rVec, string newItem) {
    rVec.push_back(newItem);
}

bool PasswordCheck(string user, string pass) {
    if(user == "Brian") {
        if(pass == "Green") {
            return true;
        } else {
            cout << "Wrong password.\n";
            return false;
        }
    }
// checks if either one or the other is true. Only one needs to be true.
    else if(user == "admin" || pass == "admin") {
        cout << "Speak friend and enter.\n";
        return true;
    }
        else if(user == "Harry" && pass == "Expelliarmus") {
            return true;
        }
    else {
        cout << "Unrecognized user.\n";
        return false;
    }
}

int main() {
    int input;
  cout << "Hello World!\n";
cout << "what would you like to triple?\n";
cin >> input;
if(input == 69) {
    cout << "Lol, nice.\n";
} else if (input == 420) {
    cout << "Lmao, funny number.\n";
}
cout << input << " * 3 = " << Triple(input) << "!\n";

    vector<string> colors = {"Red", "Green", "Blue", "Purple"};
    vector<string> enemies = {"You", "Your mom", "The Government"};
    RefAddToVector(colors, "Magenta");
        
    DisplayVec(colors);
    DisplayVec(enemies);

    cout << "Oh, I really like yellow, let's add that to the vector of colors.\n";
    colors = AddToVec(colors, "Yellow");

    cout << "Here are our colors: \n";
    DisplayVec(colors);

    // dictionaries (or maps) are a key-value pair.
    map<string, string> userpass;
    userpass["brian"] = "green";

    cout << userpass["brian"] << ".\n";

    string username;
    string password;

    cout << "Username:\n";
    cin >> username;
    cout << "Password:\n";
    cin >> password;
    
    if(password == userpass[username]) {
        cout << "success!\n";
    } else {
        cout << "Idiot.\n";
    }
      
}