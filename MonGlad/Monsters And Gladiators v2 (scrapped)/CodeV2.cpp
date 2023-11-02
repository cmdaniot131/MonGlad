#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;

struct userdata {
    char username[20];
};

struct userstats {
	int userhealth; //Permanent Health
	int zenny; //game currency
    int gsdmg; //great sword damage
    char greatsword; //weapon
};

struct weaponstore {
	char bustersword; //default weapon
	char leviathan;
	char dwleviathan;
	char hellsplitter;
	char berserkerhs;
};

void createUserFile();
void Signup(userdata& user);
void Login(userdata& user);
void mainmenu(userdata& user, userstats& ustats);
void store(weaponstore& greatswords);
void IandS(userdata& user, userstats& ustats);


int main() {
    userdata user;
    userstats ustats = {200,0,0,' '};
    weaponstore greatswords;
    int choice;
	
	char userr[250];
	
    createUserFile();

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
                Login(user);
                break;
            case 2:
                Signup(user);
                break;
            case 3:
                system("cls");
                cout << "\t\t\t\t\t\tExiting Game...." << endl;
                break;
            default:
                cout << "\t\t\t\t\t\tINVALID INPUT" << endl;
        }

    } while (choice != 3);

    return 0;
}

void createUserFile() {
    ifstream file("usersfile.txt");
    if (!file.is_open()) {
        ofstream outFile("usersfile.txt");
        if (outFile.is_open()) {
            cout << "usersfile.txt created successfully!" << endl;
            outFile.close();
        } else {
            cout << "Error creating usersfile.txt." << endl;
        }
    } else {
        file.close();
    }
}

void Signup(userdata& user, userstats& ustats) {
    ifstream inFile("usersfile.txt");
    string storedUsername;
    bool existingUsername = false;


    cout << "\n\t\t\t\t\t\tEnter Username: ";
    cin.getline(user.username, sizeof(user.username));

    while (inFile >> storedUsername) {
        if (storedUsername == user.username) {
            existingUsername = true;
            break;
        }
    }
    inFile.close();

    if (existingUsername) {
        cout << "\n\t\t\t\tUsername already exists. Please perform another registration." << endl << endl;
        system("pause");
        system("cls");
    } else {
        ofstream outFile("usersfile.txt", ios::app);
        if (outFile.is_open()) {
            outFile << user.username;
            cout << "\t\t\t\t\t\tRegistration Success! \n\n" << endl;
            outFile.close();
            system("pause");
            system("cls");
        } else {
            cout << "Error opening file" << endl;
        }
    }
}

void Login(userdata& user, userstats& ustats) {
    ifstream inFile("usersfile.txt");
    if (inFile.is_open()) {
        cout << "\n\t\t\t\t\t\tEnter username: ";
        cin >> user.username;

        string storedUsername;
        bool userExists = false;

        while (inFile >> storedUsername) {
            if (storedUsername == user.username) {
                userExists = true;
                break;
            }
        }
        inFile.close();

        if (!userExists) {
            cout << "\n\t\t\t\t\t\tLogin Failed due to Incorrect Username." << endl;
            system("pause");
            system("cls");
        } else {
            cout << "\n\t\t\t\t\t\tSuccessful Login!!" << endl;
            system("pause");
            system("cls");
            mainmenu(user, ustats);
        }
	    } else {
	        cout << "Unable to Find [usersfile.txt]" << endl;
	    }
}

void mainmenu(userdata& user, userstats& ustats) {
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

			cout << "\n\t\t\t\t\t\t1 - Levels" << endl;
			cout << "\t\t\t\t\t\t2 - Help [Game Guide]" << endl;
			cout << "\t\t\t\t\t\t3 - Store" << endl;
			cout << "\t\t\t\t\t\t4 - Inventory & User Stats" << endl;
			cout << "\t\t\t\t\t\t5 - Return to Login Page" << endl; //Returns to main menu
			cout << "\n\t\t\t\t\t\tEnter Choice: ";
			cin >> choice;
			cin.ignore();
				
				switch (choice) {
					case 1:
						system("cls");
						break;
					case 2:
						system("cls");
						break;
					case 3:
						system("cls");
						break;
					case 4:
						system("cls");
						IandS(user, ustats);
						break;
					default: 
						system("cls");
						break;
				}

    } while (choice != 5); // Returns to main menu
}

void IandS(userdata& user, userstats& ustats) {
    char choice;

    system("cls");
    printf("\t\t\t\t ___                      _                    \n"
        "\t\t\t\t|_ _|_ ____   _____ _ __ | |_ ___  _ __ _   _  \n"
        "\t\t\t\t | || '_ \\ \\ / / _ \\ '_ \\| __/ _ \\| '__| | | | \n"
        "\t\t\t\t | || | | \\ V /  __/ | | | || (_) | |  | |_| | \n"
        "\t\t\t\t|___|_| |_|\\_/ \\___|_| |_|\\__\\___/|_|   \\__, | \n"
        "\t\t\t\t              __ _ _ __   __| |         |___/  \n"
        "\t\t\t\t             / _` | '_ \\ / _` |                \n"
        "\t\t\t\t            | (_| | | | | (_| |                \n"
        "\t\t\t\t           __\\__,_|_| |_|\\__,_|                \n"
        "\t\t\t\t          / ___|| |_ __ _| |_ ___               \n"
        "\t\t\t\t          \\___ \\| __/ _` | __/ __|              \n"
        "\t\t\t\t           ___) | || (_| | |\\__ \\              \n"
        "\t\t\t\t          |____/ \\__\\__,_|\\__|___/             \n");

    
	cout << "\n\t\t\t\t-----------------Player Info-----------------" << endl;
	cout << "\n\t\t\t\tUsername   : \t" << user.username << endl;
	cout << "\n\t\t\t\t"
	
    	cout << "\n\t\t\t\tEnter 1 to return to menu: ";
    	cin >> choice;
    	
    	switch (choice) {
    		case '1':
    			mainmenu(user, ustats);
    			system("cls");
	        default:
	            break;
    	}

    
}

