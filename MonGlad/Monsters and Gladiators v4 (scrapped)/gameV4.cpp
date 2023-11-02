#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct userinfo {
    char userName[20];
};

struct userstats {
    int userhealth;
    int zenny; // ingame credits
};

struct store {
    char jawblade[20];
    char executioner[20];
    char deathscythe[20];
    char hellsplitter[20]; // Maximum Damage weapon
};

struct jawblade {
	char jb[20];
	int jbdmg;
	int jbcrit;	
};


struct starterweapon {
    char bustersword[20];
};

struct usergear {
    char equippedWeaponName[20];
    char equippedGS;
    int GSdmg;
};

void createUserFile();
void signup(userinfo &user, userstats &ustats, usergear &ugear);
void login(userinfo &user, userstats &ustats, usergear &ugear);
void mainmenu(userinfo &user, userstats &ustats, usergear &ugear);
void displaystats(const userinfo &user, const userstats &ustats, const usergear &ugear);
void store(userstats &ustats);
void savedata(const userinfo &user, const userstats &ustats, const usergear &ugear);
void loadGame(userstats &ustats);

int main() {
    userinfo user;
    userstats ustats;
    usergear ugear;
    int choice;
    
    createUserFile();
	loadGame(ustats);

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
                login(user, ustats, ugear);
                break;
            case 2:
                signup(user, ustats, ugear);
                break;
            case 3:
                system("cls");
                cout << "\t\t\t\t\tExiting game...";
                break;
            default:
                system("cls");
                cout << "\t\t\t\t\tInvalid Input!!!";
                break;
        }

        if (choice != 3 && choice != 2) {
            mainmenu(user, ustats, ugear);  // Pass ustats by reference to mainmenu
        }

    } while (choice != 3);

    return 0;
}


void createUserFile() {
    ifstream file("userdata.txt");
    if (!file.is_open()) {
        ofstream outFile("userdata.txt");
        if (outFile.is_open()) {
            cout << "userdata.txt created successfully!" << endl;
            outFile.close();
        } else {
            cout << "Error creating userdata.txt." << endl;
        }
    } else {
        file.close();
    }
}

void signup(userinfo &user, userstats &ustats, usergear &ugear) {
    ifstream inFile("userdata.txt");

    string storedusername;
    bool existingUsername = false;

    cout << "\n\t\t\t\t\t\tEnter Username: ";
    cin.getline(user.userName, sizeof(user.userName));

    while (inFile >> storedusername) {
        if (storedusername == user.userName) {
            existingUsername = true;
            break;
        }
    }
    inFile.close();

    if (existingUsername) {
        cout << "\n\t\t\t\t\tUsername already exists. Please choose another username." << endl;
        system("pause");
        system("cls");
    } else {
        ofstream outFile("userdata.txt", ios::app); // Open the file in append mode
        if (outFile.is_open()) {
            ustats.userhealth = 350; // Health
            ustats.zenny = 2000; // Starter Zenny
            strcpy(ugear.equippedWeaponName, "Buster Sword");
            outFile << "Username: " << user.userName << endl;
            outFile << "Health: " << ustats.userhealth << endl;
            outFile << "Zenny: " << ustats.zenny << endl;
            outFile << "Equipped Great Sword: " << ugear.equippedWeaponName << endl;
            outFile << "-------------------------------------\n";
            system("cls");
            cout << "\n\t\t\t\t\t\tRegistration successful!" << endl;
            outFile.close();
        } else {
            cout << "Error opening file" << endl;
        }
    }
}

void login(userinfo &user, userstats &ustats, usergear &ugear) {
    ifstream inFile("userdata.txt");

    if (inFile.is_open()) {
        string storedUsername;
        bool userExists = false;

        cout << "\n\t\t\t\t\t\tEnter username: ";
        cin.getline(user.userName, sizeof(user.userName));

        while (inFile >> storedUsername) {
            if (storedUsername == "Username: " + string(user.userName)) {
                userExists = true;
                break;
            }
        }
        inFile.close();

        if (!userExists) {
            system("cls");
            cout << "\n\t\t\t\t\t\tInvalid username. Please sign up to create a new account." << endl;
            system("pause");
            system("cls");
        } else {
            cout << "\n\t\t\t\t\t\tSuccessful Login!" << endl;
            system("pause");
            system("cls");
            mainmenu(user, ustats, ugear);
        }
    } else {
        cout << "Unable to open userdata.txt" << endl;
    }
}


void mainmenu(userinfo &user, userstats &ustats, usergear &ugear) {
    int choice;

    do {
        system("cls");
        printf(
            "\t\t\t\t  __  __  ___  _   _ ____ _____ _____ ____  ____  \n"
            "\t\t\t\t |  \\/  |/ _ \\| \\ | / ___|_   _| ____|  _ \\/ ___| \n"
            "\t\t\t\t | |\\/| | | | |  \\| \\___ \\ | | |  _| | |_) \\___ \\ \n"
            "\t\t\t\t | |  | | |_| | |\\  |___) || | | |___|  _ < ___) |\n"
            "\t\t\t\t |_|  |_|\\___/|_| \\_|____/ |_| |_____|_| \\_\\____/ \n"
            "\t\t\t\t   __ _ _ __   __| |                              \n"
            "\t\t\t\t  / _` | '_ \\ / _` |                              \n"
            "\t\t\t\t | (_| | | | | (_| |                              \n"
            "\t\t\t\t  \\__,_|_| |_|\\__,_|                              \n"
            "\t\t\t\t  ____ _        _    ____ ___    _  _____ ___  ____  ____  \n"
            "\t\t\t\t / ___| |      / \\  |  _ \\_ _|  / \\|_   _/ _ \\|  _ \\/ ___| \n"
            "\t\t\t\t| |  _| |     / _ \\ | | | | |  / _ \\ | || | | | |_) \\___ \\ \n"
            "\t\t\t\t| |_| | |___ / ___ \\| |_| | | / ___ \\| || |_| |  _ < ___) |\n"
            "\t\t\t\t \\____|_____/_/   \\_\\____/___/_/   \\_\\_| \\___/|_| \\_\\____/ \n"
        );
        cout << "\t\t\t\t\t\t[==================" << endl;
        cout << "\t\t\t\t\t\t Greatsword Edition" << endl;
        cout << "\t\t\t\t\t         ==================]" << endl;
        cout << "\t\t\t\t\t\t1. Play Game" << endl;
        cout << "\t\t\t\t\t\t2. View Stats" << endl;
        cout << "\t\t\t\t\t\t3. Store" << endl;
        cout << "\t\t\t\t\t\t4. Save Progress" << endl;
        cout << "\t\t\t\t\t\t5. Return to Login" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();
		
        switch (choice) {
            case 1:
                // Add gameplay logic here
                system("cls");
                break;
            case 2:
                displaystats(user, ustats, ugear);
                system("cls");
                break;
            case 3:
                store(ustats);  // Pass ustats by reference to store function
                break;
            case 4:
            	savedata(user, ustats, ugear);
                system("cls");
                cout << "\n\t\t\t\t\t\tData has been saved!!" << endl;
                system("pause");
                break;
            case 5:
            	system("cls");
            	break;
            default:
                cout << "\n\t\t\t\t\tInvalid Input!!!";
                break;
        }

    } while (choice != 5);
}

void displaystats(const userinfo &user, const userstats &ustats, const usergear &ugear) {
    ifstream inFile("userdata.txt");

    if (inFile.is_open()) {
        system("cls");

        cout << "\t\t\t\t\t";
        for (int i = 0; i < 46; i++) {
            cout << "*";
        }

        cout << "\n\t\t\t\t\t-----------------Player Stats-----------------" << endl;

        char line[100]; // Adjust the size according to your needs

        // Convert username to C-style string
        char username[100];
        strcpy(username, "Username: ");
        strcat(username, user.userName);

        // Read and display data line by line
        while (inFile.getline(line, sizeof(line))) {
            if (strcmp(line, username) == 0) {
                cout << line << endl;

                // Read and display the next 3 lines (assuming these are stats)
                inFile.getline(line, sizeof(line));
                cout << line << endl;
                inFile.getline(line, sizeof(line));
                cout << line << endl;
                inFile.getline(line, sizeof(line));
                cout << line << endl;

                break;
            }
        }

        inFile.close();
        system("pause");
    } else {
        cout << "Unable to open userdata.txt" << endl;
    }
}

void store(userstats &ustats) {
    int choice;
    loadGame(ustats);

    do {
        system("cls");
        cout << "\n\t\t\t\t\t------------ Store ------------" << endl;

        cout << "\t\t\t\t\t1. Buy Health Potion (500 Zenny)\n";
        cout << "\t\t\t\t\t2. Exit Store\n";
        cout << "\t\t\t\t\tCurrent Zenny: " << ustats.zenny << endl;
        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (ustats.userhealth < 350 && ustats.zenny >= 500) {
                    ustats.zenny -= 500;
                    ustats.userhealth += 50; // Increase health by 50 points for each health potion
                    if (ustats.userhealth > 350) {
                        ustats.userhealth = 350; // Ensure health doesn't exceed the maximum value
                    }
                    cout << "\n\t\t\t\t\tYou bought a health potion! Your health has been increased by 50 points." << endl;
                } else if (ustats.userhealth >= 350) {
                    cout << "\n\t\t\t\t\tYou are already at maximum health (350). Cannot buy more health potions." << endl;
                } else {
                    
                    
                }
                system("pause");
                break;
            case 2:
                break;
            default:
                cout << "\n\t\t\t\t\tInvalid Input!!!";
                system("pause");
                break;
        }
    } while (choice != 2);
}

void savedata(const userinfo &user, const userstats &ustats, const usergear &ugear) {
    ofstream outFile("userdata.txt", ios::app); // Open the file in append mode

    if (outFile.is_open()) {
        // Write data to the file
        outFile << "Username: " << user.userName << endl;
        outFile << "Health: " << ustats.userhealth << endl;
        outFile << "Zenny: " << ustats.zenny << endl;
        outFile << "Equipped Great Sword: " << ugear.equippedWeaponName << endl;
        outFile << "-------------------------------------\n";

        outFile.close();
        cout << "Player data has been saved to userdata.txt." << endl;
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
}

void loadGame(userstats &ustats) {
    ifstream inFile("userdata.txt");
    if (inFile.is_open()) {
        char rfile[100];

        // Read and discard lines until "Zenny:"
        while (inFile >> rfile) {
            if (strcmp(rfile, "Zenny:") == 0) {
                inFile >> rfile; // Read the Zenny amount
                ustats.zenny = atoi(rfile);
                break;
            }
        }

        inFile.close();
    } else {
        cout << "No saved game data found. Starting with default values." << endl;
    }
}
