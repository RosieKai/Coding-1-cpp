#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool askYN(string question) {
   do {
       cout << question << " (y/n)\n";
    char input;
    cin >> input;

       if(input == 'y') {
           return true;
       }
       if(input == 'n') {
           return false;
       }
       cout << "Uhhh, say that again? (say y or n)\n";
   }
       while (true); 
}

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

void FinalStats(int finalTurns, int finalGold, int finalOuchies) {
    cout << "\nYou took " << finalTurns << " turns.\nYou found " << finalGold << " gold.\nYou took " << finalOuchies << " points of damage.\n\n";
}

int main() {
cout << "Hey there recruit! Welcome to your first day in the Anti-Orc army! I'm your trainer, and there's no better way to learn than by doing so let's skip the formalities and go on patrol!\n";
    
    int playerHealth = 50;
    int gold = 0;
    int turns = 0;
    string input;
    int ouchies = 0;
    cout << "Are you ready to fight your first orc? (y/n)\n";
    getline(cin, input);
    if (input == "y") {
        cout << "Good to hear! Go get 'em tiger!\n";
    }
    else if (input == "n") {
        cout << "Too bad! Here it comes!\n";
    }
    else {
        cout << "I'm not totally sure what you just said but I'll take that as a yes.\n";
    }
    do {

        turns += 1;
        int damageTaken = CastDamage(1,10);
        int block = CastDamage(2,8);
        cout << "\n(A towering orc emerges from the trees and stands menacingly in your path. It charges and takes a swing at you that looks like it'd deal about " << damageTaken << " points of damage. You hurridly hoist your heafty sheild and plant your feet. You could probably block anything so long as it dealt at most " << block << " points of damage!)\n\n";

        if(block >= damageTaken) {
            playerHealth -= 1;
            ouchies += 1;
            int foundGold = DiceRoll(25);
            gold += foundGold;
            cout << "(The orc slams against your sheild with a mighty thud, you're pushed back slightly but you stay standing tall! You retaliate with a swift blow and sigh in relief when the orc falls to the ground.)\nGood job recruit! And look, he dropped " << foundGold << " gold!\n";
            //roll a 20 sided die
            
            //if it's a 20, player gets a health potion
            
            //cast damage for amount of health points regained.
        }
            
        else {
            playerHealth -= damageTaken;
            ouchies += damageTaken;
        cout << "Uh, hey don't forget-- OOF...\n(The orc soundly smacks you into the ground, dealing a whopping " << damageTaken << " points of damage. Your trainer steps in to deal with the orc personally.)\n";
        }
        
        
        
        if(playerHealth <= 0) {
            cout << "'Good job recruit, you got them! And look, they both dropped " << gold << " pieces of gold!'\n-Orc Army Trainer\n(In other words, you're dead. Sorry.)\n";
            break;
        }

        if(DiceRoll(10) == 10) {
            int price = CastDamage(20,70);
            cout << "\n\n(A tall man in a deep blue robe slinks onto the road infront of you. He reaches into his pocket and reveals a potion bottle filled with a dark red liquid,)\n'For " << price << " gold this health potion is yours! ";

                if(askYN("Do we have a deal?'")) {
                    if(gold < price) {
                        cout << "(The man smiles, then recoils as he sees you don't have enough money.)\n'Find me when you're not broke!'\n(He runs back into the forest before you can say another word.)\n\n";
                    }
                    else {
                        gold -= price;
                        cout << "(The strange man grins wide as you hand him your hard earned gold.)\n'Pleasue doing business with you.'\n(He retreats through the trees as you drink the potion.)\n";
                        int potionPoints = CastDamage(1,15);
                        if(DiceRoll(5) == 5) {
                            if(playerHealth <= potionPoints) {
                                playerHealth -= potionPoints;
                                ouchies += potionPoints;
                                cout << "(Wow, what a delicious potion! You feel like you're flying! Hey, look down there, it's Mr. Trainer! Whose body is he standing over?\nOh wait... It's you. I that potion was poisoned... Lethally.)\n";
                                break;
                            }
                            else {
                                playerHealth -= potionPoints;
                                ouchies += potionPoints;
                                cout << "(Oh no! That potion was poisoned! You lost " << potionPoints << " health!)\n\n";
                            }

                        }
                        else {
                            playerHealth += potionPoints;
                            cout << "(The vile concoction burns your throat, but at least your stab wound stopped bleeding! You gained " << potionPoints << " health!)\n\n";
                        }
                    }

                }
                else {
                    cout << "(The mysterious man narrows his eyes as he pockets the potion. He slinks back through the trees and disappears from view... Weird.)\n\n";

                }

        }
        
        cout << "\n(Turns Taken: " << turns << ")\n(You have " << playerHealth << " health left and " << gold << " gold so far.)\n";

        if(askYN("Waddya say? Ready to keep going?")) {
            cout << "Good, 'cuz here comes another one!\n";
        } else {
            cout << "D'aww, you're no fun. Fine. Let's turn back.\n";
            break;
        }
    }
        while (true);
    FinalStats(turns, gold, ouchies);
    if(playerHealth <= 0) {
        cout << "Unfortunately, that was kinda all of your health... Better luck next time...\n";
        
    }
    else if(playerHealth <= 5) {
        cout << "It's a miracle you're still alive! You should really go to a hospital... Like, right now! You only have " << playerHealth << " health left!\n";
    }
    else {
        cout << "You did good for your first day! You still have " << playerHealth << " health left so I'd say you're in pretty good shape!\n";
    }
    //ask if player wants to go on an adventure
    //if yes they are attacked by an orc
        //orc will roll for damage
        //player will roll to block
            //if block is higher than damage, player loses 1 hp, runs away, finds gold.
             //if block fails, player takes full damage, finds no gold.
        //if hp is between 5-1 they will be asked to see a doctor
        //if hp hits 0, player dies and loop breaks.
        //dead player is told how many turns they lasted and how much gold they died with.
    //if player says stop adventuring the loop breaks
    //alive player will be told how many turns they took and how much gold they found.
}