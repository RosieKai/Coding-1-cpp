#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum enemyType {android, boomba, murdrone, kerfus};

enum itemType {weapon, potion};

int DiceRoll(int sides = 6) {
    if(sides < 2) {
        sides = 2;
    }
    if (sides > 100) {
        sides = 100;
    }
    return rand() % sides + 1;
}
int CastDamage(int min, int max) {
    int damage = rand() % (max - min) + min;
    if(DiceRoll() == 6 || DiceRoll() == 10) {
        damage += damage;
    }
    return damage;
}

class item {
public:

itemType type = weapon;
int value = 0;
string name = "";
int remUses = 0;

    item (string n, itemType t) {
        name = n; 
        type = t;
        switch (type) {
            case weapon:
                value = rand() % 30 + 2;
                remUses = DiceRoll(5);
                break;
            case potion:
                value = rand() % 25 + 15;
                remUses = 999;
                break;
        }
    }
string getName() { return name; }
    int getValue() { return value; }
    int getType() { return type; }
    void dockUse() {remUses -= 1;}
    int getUses() {return remUses;}
};

vector<item> stuff;

void genItems() {
vector<string> weaponNames = {"Shock Net", "Blaster", "Plasma Rifle", "Ion Cannon", "Disintegrator", "Laser Sword", "Pulse Pistol", "Railgun", "Gravity Hammer", "Cube(?)", "Cool Stick", "Coolest Stick"};
    random_shuffle(weaponNames.begin(), weaponNames.end());
    for(int i = 0; i < weaponNames.size(); i++) {
        stuff.push_back(item(weaponNames[i], weapon));
    }
    for(int i = 0; i < 12; i++) {
        stuff.push_back(item("Potion", potion));
    }
}

item pickItem() {
    int randIndex;
        randIndex = DiceRoll(stuff.size()) - 1;
        return {stuff[randIndex]};
}

class enemy {
public:

enemyType type;
string name;
int damage;
int health;
vector<item>inventory;
int baseDamage;
int minDamage;

    enemy (string n, enemyType t) {
        name = n; 
        type = t;

        switch (type) {
            case android:
                baseDamage = rand() % 5 + 3;
                damage = baseDamage;
                minDamage = 5;
                health = rand() % 15 + 65;
                break;
            case boomba: // this is public enemy number 1
                baseDamage = rand() % 11 + 9;
                damage = baseDamage;
                minDamage = 7;
                health = rand() % 10 + 15;
                break;
            case murdrone:
                baseDamage = rand() % 5 + 6;
                damage = baseDamage;
                minDamage = 6;
                health = rand() % 10 + 70;
                break;
            case kerfus:
                baseDamage = rand() % 5 + 5;
                damage = baseDamage;
                minDamage = 5;
                health = rand() % 20 + 80;
                break;
        }
    }

    string getName() { return name; }
    int getHealth() { return health; }
    int getDamage() { return damage; }
    int getType() { return type; }

    string typeToString(enemyType type) {
        // this is a switch statement. it's like a multiple choice if statement
        // only has to test once. All possible values are mapped.
    switch(type) {
        case android: return "android"; break;
        case boomba: return "boomba"; break;
        case murdrone: return "murdrone"; break;
        case kerfus: return "kerfus"; break;
        default: return "unknown"; break;
        }
    }

    void addItem(item i) {
        inventory.push_back(i);
        updateDamage(i);
    }

    void printInventory() {
        cout << "Inventory: " << endl;
        for (int i = 0; i < inventory.size(); i++) {
        cout << i << ": " << inventory[i].getName() << endl;
        }
    }
    void updateDamage(item item) {
        damage = baseDamage;
        for (int i = 0; i < inventory.size(); i++) {
            if (item.getType() == weapon) {
        damage += item.getValue();
            }
        }
    }
    void addHealth(item item) {
        if (item.getType() == potion) {
            health += item.getValue();
        }
    }
    void takeDamage(int ouch) {
        health -= ouch;
    }
    int attack() {
        int attack = CastDamage(minDamage, damage);
        return attack;
    }
    
};

vector<enemy> roboEnemies;
void genEnem() {

    vector<string> androidNames = {"DAVE", "Crusher", "Arnold", "Jake", "Walter"};
    vector<string> boombaNames = {"Evacuumater", "Beepers", "Mr. Boom", "McRowav", "Dee Molison"};
    vector<string> murdoneNames = {"SD-N", "Maya", "Oozie", "J", "Syn"};
    vector<string> kerfusNames = {"Fluffy", "Mittens", "Purfur", "Sweetie", "Bastard"};

    random_shuffle(androidNames.begin(), androidNames.end());
    random_shuffle(boombaNames.begin(), boombaNames.end());
    random_shuffle(murdoneNames.begin(), murdoneNames.end());
    random_shuffle(kerfusNames.begin(), kerfusNames.end());

    for(int i = 0; i < androidNames.size(); i++) {
        roboEnemies.push_back(enemy(androidNames[i], android));
    }
    for(int i = 0; i < boombaNames.size(); i++) {
        roboEnemies.push_back(enemy(boombaNames[i], boomba));
    }
    for(int i = 0; i < murdoneNames.size(); i++) {
        roboEnemies.push_back(enemy(murdoneNames[i], murdrone));
    }
    for(int i = 0; i < kerfusNames.size(); i++) {
        roboEnemies.push_back(enemy(kerfusNames[i], kerfus));
    }
}

void enemyDeath(enemy e) {
    roboEnemies.erase(roboEnemies.begin() + (e.getType()));
}

class player {
public:

int damage;
int health;
vector<item>inventory;
string name;
int baseDamage;
int minDamage;
    player (string n) {
        name = n;
        health = 100;
        baseDamage = rand() % 28 + 7;
        damage = baseDamage;
        minDamage = 7;
    }
    void printInventory() {
        cout << "Inventory: " << endl;
        for (int i = 0; i < inventory.size(); i++) {
        cout << i << ": " << inventory[i].getName() << endl;
        }
    }
    void resetDamage() {damage = baseDamage;}
    void updateDamage(item item) {
        resetDamage();
        for (int i = 0; i < inventory.size(); i++) {
            if (item.getType() == weapon) {
        damage += item.getValue();
            }
        }
    }
    void subtractDamage(item item) {
        damage -= item.getValue();
    }
    void addHealth(item item) {
        if (item.getType() == potion) {
            health += item.getValue();
        }
    }
    string getName() { return name; }
    void printName() {cout << "You are " << name << ".\n";}
    void addItem(item i) {
        inventory.push_back(i);
        updateDamage(i);
    }
    int attack() {
        int attack = CastDamage(minDamage, damage);
        return attack;
    }
    void takeDamage(int ouch) {
        health -= ouch;
    }

    int getHealth() { return health; }

    void breakItem(item i) {
        inventory.erase(inventory.begin() + (i.getType()));
    }
};

// void itemWear(item i, player p) {
//     i.dockUse();
//     if (i.getUses() <= 0) {
//         cout << i.getName() << " broke!\n";
//         p.breakItem(i);
//     stuff.erase(stuff.begin() + (i.getType() - 1)); 
//         p.updateDamage(i);
//     }
// }

enemy pickEnem() {
    int randIndex;
        randIndex = DiceRoll(roboEnemies.size()) - 1;
        return {roboEnemies[randIndex]};
}

void PrintStats(int takenTurns, int killCount, int Health, int damageDealt, int damageTaken, int potionsDrank) {
    cout << "\nYour Stats:\n\nTurns: " << takenTurns << "\nKills: " << killCount << "\nHealth: " << Health << "\nDamage Dealt: " << damageDealt << "\nDamage Taken: " << damageTaken << "\nPotions Drank: " << potionsDrank << "\n";
}

int main() {
    srand(time(0));
    string tempName;
    
    cout << "Enter name:\n";
    getline(cin, tempName);
    
    player player1(tempName);
    item sword("sword", weapon);
    item potion1("Potion", potion);
    item potion2("Potion", potion);
    player1.addItem(sword);
    player1.updateDamage(sword);
    player1.addItem(potion1);
    player1.addItem(potion2);
    genEnem();
    genItems();
    int weaponCount = 1;
    
    cout << "Welcome to the tournament, " << tempName << "! Defeat 12 robots to win.\nGood luck!\n";

    int turns = 0;
    int kills = 0;
    int drinks = 0;
    int plOuchies = 0;
    int enemOuchies = 0;
    int plHealth = player1.getHealth();
    string input;
    do {
        enemy currentEnemy = pickEnem();
        currentEnemy.addItem(pickItem());
        enemyType robo = (enemyType)currentEnemy.getType();
        // currentEnemy.addItem(pickItem());
        cout << "\nWould you like to:\n\n";
        cout << "View Inventory = 1\nView Stats = 2\nConfront New Opponent = 3\nLeave = 4\n";
        getline(cin, input);
        if (input == "1") {
            player1.printInventory();
        }
        else if (input == "2") {
            PrintStats(turns, kills, plHealth, enemOuchies, plOuchies, drinks);
        }
        else if (input == "3") {
            do {
                turns += 1;
                cout << "In front of you stands a terrifying " << currentEnemy.typeToString(robo) << " named " << currentEnemy.getName() << " with " << currentEnemy.getHealth() << " health!\n";
                cout << "\nAttack = 1\nDrink Potion = 2\nFlee = 3\n";
                getline(cin, input);
                if (input == "1") {
                    int playerAttack = player1.attack();
                    currentEnemy.takeDamage(playerAttack);
                    enemOuchies += playerAttack;
                    cout << "You attack " << currentEnemy.getName() << " for " << playerAttack << " damage!\n";
                    if (weaponCount >= 1) {
                       for (int i = 0; i < player1.inventory.size(); i++) {
                        if (player1.inventory[i].getType() == weapon) {
                            player1.inventory[i].dockUse();
                            if (player1.inventory[i].getUses() <= 0) {
                                cout << player1.inventory[i].getName() << " broke!\n";
                                player1.subtractDamage(player1.inventory[i]);
                                stuff.erase(stuff.begin() + (player1.inventory[i].getType())); 
                                player1.breakItem(player1.inventory[i]);
                                weaponCount -= 1;
                                }
                            }
                        } 
                    }
                    
                    if (currentEnemy.getHealth() <= 0) {
                        kills += 1;
                        cout << "Congrats! " << currentEnemy.getName() << " has been defeated!\n";
                        for(int i = 0; i < currentEnemy.inventory.size(); i++) {
                            player1.addItem(currentEnemy.inventory[i]);
                            if (currentEnemy.inventory[i].getType() == weapon) {weaponCount += 1;}
                            cout << "You picked up a(n) " << currentEnemy.inventory[i].getName() << "!\n";
                            currentEnemy.inventory.erase(currentEnemy.inventory.begin() + i);
                        }
                        enemyDeath(currentEnemy);
                        break;
                    }
                }
                else if (input == "2") {
                    for (int i = 0; i < player1.inventory.size(); i++) {
                        if (player1.inventory[i].getType() == potion) {
                            player1.addHealth(player1.inventory[i]);
                            player1.inventory.erase(player1.inventory.begin() + i);
                            cout << "You drank a potion and gained " << player1.inventory[i].getValue() << " health!\n";
                            drinks += 1;
                        }
                        else if (i == player1.inventory.size() - 1) {
                            cout << "You have no potions!\n";
                        }
                    }
                }
                else if (input == "3") {
                    break;
                }
                else {
                    cout << "Invalid input.\n";
                }
                int enemyAttack = currentEnemy.attack();
                    player1.takeDamage(enemyAttack);
                    plOuchies += enemyAttack;
                cout << currentEnemy.getName() << " attacked you for " << enemyAttack << " damage!\n";
                    if (player1.getHealth() <= 0) {
                        cout << "You have been defeated by " << currentEnemy.getName() << ".\n";
                        break;
                    }
            }
            while(true);
        }
        else if (input == "4") {break;}
        else {cout << "Invalid Option\n";}
        plHealth = player1.getHealth();
        if (player1.getHealth() <= 0) {
            PrintStats(turns, kills, plHealth, enemOuchies, plOuchies, drinks);
            break;
        }
        if (kills == 12) {
            cout << "Ladies, gentlemen, and other, we have a winner! Give it up for " << player1.getName() << ", our tournament champion!";
            PrintStats(turns, kills, plHealth, enemOuchies, plOuchies, drinks);
            break;
        }
    }
    while (true);
    
}