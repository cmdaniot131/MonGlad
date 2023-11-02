#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

struct LogInfo {
    string username;
};

struct UserStats {
    int userhealth;
    int healthpots;
    int userzenny;
    string GSname;
    int equippedGSdmg;
};

struct Weapon {
    string name;
    int damage;
    int crit;
};

struct Monster {
	string name;
	int health;
	int damage;
};

Monster monster;
Monster kulu = {"Kulu-Ya-Ku", 450, 40};
Monster bar = {"Barroth", 500 , 60};
Monster dia = {"Diablos", 650, 80};
Weapon buster = {"Buster Sword", 50, 5}; 
Weapon deathScythe = {"Death Scythe", 80, 30};
Weapon hellSplitter = {"Hell Splitter", 125, 45};

void createFile();
bool attack();
bool login(LogInfo &user);
void signup(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon);
void mainmenu(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon, Monster &monster, Monster &kulu);
//void viewStats(const LogInfo &user, const UserStats &ustats, const Weapon &selectedWeapon);
void store(UserStats &ustats, Weapon &selectedWeapon);
void atkmonster(UserStats &player, Monster &monster, Monster &kulu); //Player Attacks the monster
void monsteratk(UserStats &player, Monster &monster, Monster &kulu); //Monster Attacks the player
void monster1battle(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon, Monster &monster, Monster &kulu);
void saveData(const LogInfo &user, const UserStats &ustats, const Weapon &selectedWeapon);

int main() {
	srand((unsigned)time(NULL));
    LogInfo user;
    UserStats ustats;
    
    Weapon selectedWeapon = buster; 
    
    int choice;
    createFile();

    do {
        cout << "\n\t\t\t\t\t       [============" << endl;
        cout << "\t\t\t\t\t\tLogin System" << endl;
        cout << "\t\t\t\t\t        ============]\n" << endl;
        cout << "\t\t\t\t\t\t1. Login" << endl;
        cout << "\t\t\t\t\t\t2. Register" << endl;
        cout << "\t\t\t\t\t\t3. Exit" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (login(user)) {
                    system("cls");
                    cout << "\n\t\t\t\t\t\tSuccessful Login!!" << endl;
                    system("pause");
                    system("cls");
                    mainmenu(user, ustats, selectedWeapon, monster, kulu);
                } else {
                    system("cls");
                    cout << "\n\t\t\t\t\t\tLogin Failed due to Incorrect Username." << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case 2:
                signup(user, ustats, selectedWeapon);
                system("cls");
                cout << "\n\t\t\t\t\tRegistration Success! \n" << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                cout << "\t\t\t\t\tExiting game...";
                system("cls");
                break;
            default:
                cout << "\t\t\t\t\tInvalid Input!!!";
                break;
        }

    } while (choice != 3);

    return 0;
}

void createFile() {
    ifstream inFile("userdata.txt");
    if (!inFile) {
        ofstream outFile("userdata.txt");
        if (!outFile) {
            cout << "Error creating userdata.txt" << endl;
        } else {
            outFile.close();
        }
    } else {
        inFile.close();
    }
}

bool attack() {
	return rand() % 2 == 0;
}

bool login(LogInfo &user) {
    ifstream inFile("userdata.txt");
    if (inFile.is_open()) {
        string storeduser;
        string input;
        bool existingUser = false;

        cout << "\n\t\t\t\t\tEnter Username: ";
        getline(cin, input);

        while (getline(inFile, storeduser)) {
            if (storeduser == input) {
                existingUser = true;
                break;
            }
        }
        inFile.close();

        if (!existingUser) {
            return false; // Username not found
        } else {
            user.username = input;
            return true; // Successful login
        }
    }
    return false; // File not found or other error
}

void signup(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon) {
    ofstream outFile("userdata.txt" /*,ios::app*/);
    if (outFile.is_open()) {
        cout << "\n\t\t\t\t\tEnter Username: ";
        getline(cin, user.username);

        // Initialize userstats
        ustats.userhealth = 200;
        ustats.healthpots = 0;
        ustats.userzenny = 2000;
        ustats.GSname = "Buster Sword";
        ustats.equippedGSdmg = 50;

        // Save user data
        outFile << user.username << endl;
        outFile << ustats.userhealth << endl;
        outFile << ustats.healthpots << endl;
        outFile << ustats.userzenny << endl;
        outFile << ustats.GSname << endl;
        outFile << ustats.equippedGSdmg << endl;
        outFile << "-------------------------------------\n" << endl;

        // Set default weapon
        selectedWeapon = buster;

        outFile.close();
    } else {
        cout << "Error opening userdata.txt" << endl;
    }
}

//void viewStats(const LogInfo &user, const UserStats &ustats, const Weapon &selectedWeapon) {
//    system("cls"); // Clear the console screen
//    cout << "\n\t\t\t\t\t-----------------Player Stats-----------------" << endl;
//    cout << "\t\t\t\t\tUsername: " << user.username << endl;
//    cout << "\t\t\t\t\tHealth: " << ustats.userhealth << endl;
//    cout << "\t\t\t\t\tHealth Potions: " << ustats.healthpots << endl;
//    cout << "\t\t\t\t\tZenny: " << ustats.userzenny << endl;
//    cout << "\t\t\t\t\tWeapon: " << selectedWeapon.name << endl;
//    cout << "\t\t\t\t\tDamage: " << selectedWeapon.damage << endl;
//    cout << "\t\t\t\t\tCritical Damage: " << selectedWeapon.crit << "%" << endl;
//    cout << "\t\t\t\t\t";
//    for (int i = 0; i < 46; i++) {
//        cout << "-";
//    }
//    cout << endl;
//}

void store(UserStats &ustats, Weapon &selectedWeapon) {
    int choice;
    do {
        system("cls"); // Clear the console screen
        cout << "\n\t\t\t\t\t------------ Store ------------" << endl;
        cout << "\t\t\t\t\tCurrent Zenny: " << ustats.userzenny << endl; // Display current Zenny
        cout << "\t\t\t\t\t1. Buy Health Potion (500 Zenny)" << endl;
        cout << "\t\t\t\t\t2. Buy Death Scythe (1500 Zenny)" << endl;
        cout << "\t\t\t\t\t3. Buy Hell Splitter (2000 Zenny)" << endl;
        cout << "\t\t\t\t\t4. Exit Store" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (ustats.userzenny >= 500) {
                    ustats.userzenny -= 500;
                    ustats.healthpots++;
                    cout << "\t\t\t\t\tHealth Potion purchased! Current Zenny: " << ustats.userzenny << endl;
                } else {
                    cout << "\n\t\t\t\t\tNot enough Zenny to buy a health potion." << endl;
                }
                break;
            case 2:
                if (ustats.userzenny >= 1500) {
                    ustats.userzenny -= 1500;
                    selectedWeapon = deathScythe;
                    cout << "\t\t\t\t\tDeath Scythe purchased! Current Zenny: " << ustats.userzenny << endl;
                } else {
                    cout << "\n\t\t\t\t\tNot enough Zenny to buy Death Scythe." << endl;
                }
                break;
            case 3:
                if (ustats.userzenny >= 2000) {
                    ustats.userzenny -= 2000;
                    selectedWeapon = hellSplitter;
                    cout << "\t\t\t\t\tHell Splitter purchased! Current Zenny: " << ustats.userzenny << endl;
                } else {
                    cout << "\n\t\t\t\t\tNot enough Zenny to buy Hell Splitter." << endl;
                }
                break;
            case 4:
                cout << "Exiting store..." << endl;
                break;
            default:
                cout << "\n\t\t\t\t\tInvalid Input!!!" << endl;
                break;
        }

        system("pause"); // Pause the program to display messages
    } while (choice != 4);
}

void atkmonster(UserStats &player, Monster &monster, Monster &kulu) {
    if (attack()) {
        int damage = player.equippedGSdmg;
        monster.health -= damage;
        cout << "You attacked the monster and dealt " << damage << " damage" << endl;
    } else {
        cout << "Your attack missed!" << endl;
    }
}

void monsteratk(UserStats &player, Monster &monster, Monster &kulu) {
    if (attack()) {
        int damage = monster.damage;
        player.userhealth -= damage;
        cout << "The monster attacked and dealt " << damage << " damage to you" << endl;
    } else {
        cout << "The monster's attack missed!" << endl;
    }
}

void monster1battle(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon, Monster &monster, Monster &kulu) {
    cout << "\n\t\t\t\t\tPrepare for battle with Kulu-Ya-Ku!" << endl;

    while (kulu.health > 0 && ustats.userhealth > 0) {
        int choice;
        cout << "\n\t\t\t\t\t[===================" << endl;
        cout << "\t\t\t\t\t   Battle Menu" << endl;
        cout << "\t\t\t\t\t===================]\n" << endl;
        cout << "\t\t\t\t\tMonster HP: " << kulu.health << endl;
        cout << "\t\t\t\t\tYour HP: " << ustats.userhealth << endl;
        cout << "\t\t\t\t\t1. Attack" << endl;
        if (ustats.userhealth < 200) {
            cout << "\t\t\t\t\t2. Use Health Potion (" << ustats.healthpots << " available)" << endl;
        } else {
            cout << "\t\t\t\t\t2. Use Health Potion (Cannot heal further)" << endl;
        }
        cout << "\t\t\t\t\t3. Run" << endl;
        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                atkmonster(ustats, monster, kulu); // Player attacks the monster
                monsteratk(ustats, monster, kulu); // Monster counter-attacks
                break;
            case 2:
                if (ustats.userhealth < 200 && ustats.healthpots > 0) {
                    ustats.healthpots--;
                    ustats.userhealth += 50; // Using a health potion restores 50 health points
                    if (ustats.userhealth > 200) {
                        ustats.userhealth = 200; // Ensure user's health does not exceed the maximum (200)
                    }
                    cout << "\n\t\t\t\t\tYou used a health potion. Current Health: " << ustats.userhealth << endl;
                } else if (ustats.userhealth >= 200) {
                    cout << "\n\t\t\t\t\tYour health is already at maximum. Cannot heal further." << endl;
                } else {
                    cout << "\n\t\t\t\t\tNo health potions available!" << endl;
                }
                monsteratk(ustats, monster, kulu); // Monster attacks after using the health potion
                break;
            case 3:
                cout << "\n\t\t\t\t\tYou ran away from the battle." << endl;
                return; // Exit the function and return to the main menu
            default:
                cout << "\n\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        // Check if the player or the monster is defeated
        if (kulu.health <= 0) {
            cout << "\n\t\t\t\t\tYou defeated Kulu-Ya-Ku! You gained 600 zenny as a reward." << endl;
            ustats.userzenny += 600; // Reward the player with 600 zenny
            cout << "\t\t\t\t\tTotal Zenny: " << ustats.userzenny << endl;
            // Handle additional reward logic if needed
            // Increase user's stats, provide items, etc.
        } else if (ustats.userhealth <= 0) {
            cout << "\n\t\t\t\t\tKulu-Ya-Ku defeated you. Game over." << endl;
            // Implement game over logic (redirect to main menu or exit the game)
        }
    }
}

void mainmenu(LogInfo &user, UserStats &ustats, Weapon &selectedWeapon, Monster &monster, Monster &kulu) {
    system("cls");
    int choice;

    do {
        cout << "\n\t\t\t\t\t       [============" << endl;
        cout << "\t\t\t\t\t\tMain Menu" << endl;
        cout << "\t\t\t\t\t        ============]\n" << endl;
        cout << "\t\t\t\t\t\t1. Play Game" << endl;
        cout << "\t\t\t\t\t\t2. View Stats" << endl;
        cout << "\t\t\t\t\t\t3. Visit Store" << endl;
        cout << "\t\t\t\t\t\t4. Save Progress" << endl;
        cout << "\t\t\t\t\t\t5. Logout" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
            	int battlechoice;
                cout << "\t\t\t\t\t1. Kulu-Ya-Ku Battle" << endl;
                cout << "\t\t\t\t\t2. Barroth Battle" << endl;
                cout << "\t\t\t\t\t3. Diablos Battle" << endl;
                cout << "\n\t\t\t\t\tEnter your choice: " << endl;
                cin >> battlechoice;
                
                switch (battlechoice) {
                	case 1:
                		monster1battle(user, ustats, selectedWeapon, monster, kulu);
                		break;
                	default:
                		cout << "INVALID INPUT!!" << endl;
                		break;
				}
                
                break;
            case 2:
                //viewStats(user, ustats, selectedWeapon);
                break;
            case 3:
                store(ustats, selectedWeapon);
                break;
            case 4:
                saveData(user, ustats, selectedWeapon);
                cout << "\n\t\t\t\t\t\tData has been saved!!" << endl;
                break;
            case 5:
                cout << "\n\t\t\t\t\t\tLogging out..." << endl;
                system("cls");
                break;
            default:
                cout << "\n\t\t\t\t\tInvalid Input!!!" << endl;
                break;
        }

    } while (choice != 5);
}

void saveData(const LogInfo &user, const UserStats &ustats, const Weapon &selectedWeapon) {
    ofstream outFile("userdata.txt");
    if (outFile.is_open()) {
        outFile << user.username << endl;
        outFile << ustats.userhealth << endl;
        outFile << ustats.healthpots << endl; 
        outFile << ustats.userzenny << endl;
        outFile << selectedWeapon.name << endl;
        outFile << selectedWeapon.damage << endl;
        outFile << selectedWeapon.crit << endl;
        outFile << "-------------------------------------\n" << endl;
        outFile.close();
    } else {
        cout << "Error opening userdata.txt" << endl;
    }
}

