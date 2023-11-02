#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

struct userinfo {
	char userName[20];
};

struct userstats {
	int userhealth;
	int zenny; //ingame credits
};

struct weaponstore {
	char bustersword; //default starter weapon
	char jawblade;
	char executioner;
	char deathscythe;
	char hellsplitter;
};

struct usergear {
	char equippedGS;
	int GSdmg;
};

void createUserFile();
void Signup(userinfo user[], userstats ustats[], usergear ugear[], int size);
void Login(userinfo user[], userstats ustats[], usergear ugear[], int size);
void mainmenu(userinfo user[], userstats ustats[], usergear ugear[], int size);
void levels();
void help();
void store();
void IandS(const userinfo user[], const userstats ustats[], const usergear ugear[], int size); //DISPLAY DATA OF USER

int main(int argc, char** argv) {
	
	userinfo user[3];
	userstats ustats[3];
	weaponstore wstoregears[5];
	usergear ugear[3];
	int choice;
	
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
                Login(user, ustats, ugear, 3);
                break;
            case 2:
                Signup(user, ustats, ugear, 3);
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
            //cout << "usersfile.txt created successfully!" << endl; 
            outFile.close();
        } else {
            cout << "Error creating usersfile.txt." << endl;
        }
    } else {
        file.close();
    }
}

void Signup(userinfo user[], userstats ustats[], usergear ugear[], int size) {
	ifstream inFile("usersfile.txt");
	
	userinfo newUser;
	userstats newStats;
	usergear equippedgs;
	string storedusername;
	bool existingUsername = false;
	
	cout << "\n\t\t\t\t\t\tEnter Username: ";
	cin.getline(newUser.userName, sizeof(newUser.userName));
	
	while (inFile >> storedusername) {
        if (storedusername == newUser.userName) {
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
            ustats[0].userhealth = 200;
            ustats[0].zenny = 0;
            ugear[0].equippedGS = 'A';
            outFile << "Username: " << newUser.userName << endl;
            outFile << "Health: " << ustats[0].userhealth << endl;
            outFile << "Zenny: " << ustats[0].zenny << endl;
            outFile << "Equipped Great Sword: " << ugear[0].equippedGS << endl;
            outFile << "-------------------------------------\n";
            outFile.close();
            cout << "\t\t\t\t\t\tRegistration Success! \n\n" << endl;
            system("pause");
            system("cls");
        } else {
            cout << "Error opening file" << endl;
        }
    }
	
}

void Login(userinfo user[], userstats ustats[], usergear ugear[], int size) {
	ifstream inFile("usersfile.txt");
	
	if (inFile.is_open()) {
		string storedUsername;
		char inputUser[20];
    	bool userExists = false;
		
		cout << "\n\t\t\t\t\t\tEnter username: ";
		cin.getline(inputUser, sizeof(inputUser));
		
		while (inFile >> storedUsername) {
			if (storedUsername == inputUser) {
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
            mainmenu(user, ustats, ugear, 3);
        }
        
	} else {
		cout << "Unable to Find [usersfile.txt]" << endl;
	}
		
}

void mainmenu(userinfo user[], userstats ustats[], usergear ugear[], int size) {
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
						IandS(user, ustats, ugear, 3);
						break;
					default: 
						system("cls");
						break;
				}

    } while (choice != 5);
}

void levels () { //5 monsters depending on their own difficulty
	
}

void help () { //Guide for the game
}

void store() {
	
}

void IandS(const userinfo user[], const userstats ustats[], const usergear ugear[], int size) {
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

    cout << "\n\t\t\t\t -----------------Player Info-----------------" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "\t\t\t\t Username: " << user[i].userName << endl;
        cout << "\t\t\t\t Health: " << ustats[i].userhealth << endl;
        cout << "\t\t\t\t Zenny: " << ustats[i].zenny << endl;
        cout << "\t\t\t\t Equipped Great Sword: " << ugear[i].equippedGS << endl;
        cout << "\t\t\t\t-----------------------------------------------" << endl;
    }

    cout << "\n\t\t\t\tPress Enter to return to the main menu...";
    cin.ignore(); // Wait for user input
}
