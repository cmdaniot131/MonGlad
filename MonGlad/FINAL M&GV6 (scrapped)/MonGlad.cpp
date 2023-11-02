#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

struct userinfo {
	string username;
	int userzenny;
	int healthpots;
	string equippedGS;
	int equippedGSdmg;
};

struct weapon {
	string name;
	int damage;
};

struct monster {
	string name;
};

void createFile();
void ureg(userinfo &uinfo, weapon &buster);
void ulog(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu);
void store(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter);
void battlekulu(userinfo &uinfo, monster &kulu);
void arena(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu);
void mainmenu(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu);
void save(const userinfo &uinfo);

int main(int argc, char** argv) {
	
	srand((unsigned)time(NULL));
	userinfo uinfo;
	weapon buster = {"Buster Sword", 50}; 
	weapon deathscythe = {"Death Scythe", 80};
	weapon hellsplitter = {"Hell Splitter", 125};
	monster kulu = {"Kulu-Ya-Ku"};
	monster bar = {"Barroth"};
	monster dia = {"Diablos"};
	
	int choice;
	createFile();
	
	do {
		
		cout << "\n\t\t\t\t\t       [============" << endl;
        cout << "\t\t\t\t\t\tLogin System" << endl;
        cout << "\t\t\t\t\t        ============]\n" << endl;
        cout << "\t\t\t\t\t\t1. Register" << endl;
        cout << "\t\t\t\t\t\t2. Login" << endl;
        cout << "\t\t\t\t\t\t3. Exit" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();
		
		switch (choice) {
			case 1:
				ureg(uinfo, buster);
				system("cls");
				break;
			case 2:
				ulog(uinfo, buster, deathscythe, hellsplitter, kulu);
				break;
			case 3:
				cout << "\t\t\t\t\t\tExiting game...";
                system("cls");
                break;
            default:
            	system("cls");
            	cout << "\t\t\t\t\t\tInvalid Input!!!";
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

void ureg(userinfo &uinfo, weapon &buster) {
    ifstream inFile("userdata.txt");
    userinfo newUser;
    
    string storedusername;
    bool existingUser = false;
    
    cout << "\n\t\t\t\t\t\tEnter New Username: ";
    getline(cin, newUser.username);
    
    while (inFile >> storedusername) {
        if (storedusername == newUser.username) {
            existingUser = true;
            break;
        }
    }
    inFile.close();
    
    if (existingUser) {
        cout << "\n\t\t\t\t\t\tUsername already exists. Please perform another registration" << endl;
        system("pause");
        system("cls");
    } else {
        ofstream outFile("userdata.txt", ios::app);
        newUser.equippedGS = buster.name;
        newUser.equippedGSdmg = buster.damage;
        newUser.userzenny = 2000;
        newUser.healthpots = 0;
        outFile << newUser.username << endl;
        outFile << newUser.userzenny << endl;
        outFile << newUser.equippedGS << endl;
        outFile << newUser.equippedGSdmg << endl;
        outFile << newUser.healthpots << endl;
        outFile.close();
        cout << "\n\t\t\t\t\t\tRegistration Successful!" << endl;
        system("pause");
        system("cls");
    }
}


void ulog(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu) {
    ifstream inFile("userdata.txt");
    
    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt";
    } else {
        string storedusername;
        string uinput;
        bool existingUser = false;
        
        cout << "\n\t\t\t\t\t\tEnter Username: " << endl;
        getline(cin, uinput);
        
        existingUser = false;
        
        while (inFile >> storedusername) {
            if (storedusername == uinput) {
                existingUser = true;
                if (inFile >> uinfo.userzenny) {
                    break;
                }
                if (inFile >> uinfo.equippedGS) {
                	break;
				}
				if (inFile >> uinfo.equippedGSdmg) {
					break;
				}
				if (inFile >> uinfo.healthpots) {
                	break;
				}
            }
        }
        inFile.close();
        
        if (!existingUser) {
            cout << "\n\t\t\t\t\t\tLogin Failed. Please try again" << endl;
            system("pause");
            system("cls");
        } else {
            cout << "\n\t\t\t\t\t\tSuccessful Login!!" << endl;
            system("pause");
            system("cls");
            mainmenu(uinfo, buster, deathscythe, hellsplitter, kulu);
        }
    }
}

void store(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter) {
    system("cls");
    int choice;
    
    ifstream inFile("userdata.txt");

    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt" << endl;
        return;
    }
    inFile.close();



    do {
        cout << "\n\t\t\t\t\t------------ Colosseum Store ------------" << endl;
    	cout << "\t\t\t\t\tCurrent Zenny: " << uinfo.userzenny << endl; // Display current Zenny
        cout << "\t\t\t\t\t1. Buy Health Potion (500 Zenny)" << endl;
        cout << "\t\t\t\t\t2. Buy Death Scythe (1500 Zenny)" << endl;
        cout << "\t\t\t\t\t3. Buy Hell Splitter (2000 Zenny)" << endl;
        cout << "\t\t\t\t\t4. Exit Store" << endl;
        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                if (uinfo.userzenny >= 500) {
                	uinfo.userzenny -= 500;
                	uinfo.healthpots++;
                	system("cls");
                	cout << "\t\t\t\t\tYou have purchased a health potion! Current Health Potions: " << uinfo.healthpots << endl;
                	system("pause");
                	save(uinfo);
				} else {
					cout << "\t\t\t\t\tNot enough Zenny to buy a health potion. Go win some battles first!" << endl;
				}
				system("pause");
                break;
            case 2:
                system("cls");
                if (uinfo.userzenny >= 1500 && uinfo.equippedGS != deathscythe.name) {
                    uinfo.userzenny -= 1500;
                    uinfo.equippedGS = deathscythe.name;
                    uinfo.equippedGSdmg = deathscythe.damage;
                    cout << "\t\t\t\t\tYou have purchased Death Scythe! Current Equipped Weapon: " << uinfo.equippedGS << endl;
                    save(uinfo);
                } else if (uinfo.equippedGS == deathscythe.name) {
                    cout << "\t\t\t\t\tYou already have this item!" << endl;
                } else {
                    cout << "\t\t\t\t\tNot enough Zenny to buy Death Scythe. Go win some battles first!" << endl;
                }
                system("pause");
                break;
            case 3:
                system("cls");
			    if (uinfo.userzenny >= 3000 && uinfo.equippedGS != hellsplitter.name) {
			        uinfo.userzenny -= 3000;
			        uinfo.equippedGS = hellsplitter.name;
			        uinfo.equippedGSdmg = hellsplitter.damage;
			        cout << "\t\t\t\t\tYou have purchased Hell Splitter! Current Equipped Weapon: " << uinfo.equippedGS << endl;
			        save(uinfo); // Save the game after purchasing Hell Splitter
			    } else if (uinfo.equippedGS == hellsplitter.name) {
			        cout << "\t\t\t\t\tYou already have this item!" << endl;
			    } else {
			        cout << "\t\t\t\t\tNot enough Zenny to buy Hell Splitter. Go win some battles first!" << endl;
			    }
			    system("pause");
			    break;
                break;
            case 4:
                system("cls");
                break;
            default:
            	system("cls");
                cout << "\t\t\t\t\tInvalid Input!!!";
                break;
        }
        
    } while (choice != 4);
}

void battlekulu(userinfo &uinfo, monster &kulu) {
    int playerHealth = 100; // Player's initial health
    int monsterHealth = 150; // Kulu-Ya-Ku's initial health
    int damage;

    system("cls");
    cout << "\n\t\t\t\t\t\tPrepare for battle! You are facing Kulu-Ya-Ku." << endl;
    system("pause");
    system("cls");

    while (playerHealth > 0 && monsterHealth > 0) {
        cout << "\t\t\t\t\t\tYour Health: " << playerHealth << "\t\tKulu-Ya-Ku's Health: " << monsterHealth << endl;
        cout << "\n\t\t\t\t\t\t1. Attack" << endl;
        cout << "\t\t\t\t\t\t2. Use Health Potion (Remaining: " << uinfo.healthpots << ")" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // Implement a 50/50 chance of landing an attack
                if (rand() % 2 == 0) {
                    // Calculate damage based on equipped weapon damage
                    damage = rand() % uinfo.equippedGSdmg + 1;
                    monsterHealth -= damage;
                    cout << "\n\t\t\t\t\t\tYou dealt " << damage << " damage to Kulu-Ya-Ku!" << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYour attack missed!" << endl;
                }
                break;
            case 2:
                // Use a health potion if the player has any
                if (uinfo.healthpots > 0) {
                    playerHealth += 30; // Health potion restores 30 health points
                    uinfo.healthpots--; // Decrease the number of health potions
                    cout << "\n\t\t\t\t\t\tYou used a health potion. Restored 30 health points." << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYou don't have any health potions left!" << endl;
                }
                break;
            default:
                cout << "\n\t\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        // Implement a 50/50 chance of Kulu-Ya-Ku landing an attack
        if (rand() % 2 == 0) {
            damage = rand() % 20 + 1; // Kulu-Ya-Ku's damage between 1 and 20
            playerHealth -= damage;
            cout << "\n\t\t\t\t\t\tKulu-Ya-Ku dealt " << damage << " damage to you!" << endl;
        } else {
            cout << "\n\t\t\t\t\t\tKulu-Ya-Ku's attack missed!" << endl;
        }

        system("pause");
        system("cls");
    }

    // Check the battle result
    if (playerHealth <= 0) {
        cout << "\n\t\t\t\t\t\tYou were defeated by Kulu-Ya-Ku. Better luck next time!" << endl;
    } else {
        cout << "\n\t\t\t\t\t\tCongratulations! You defeated Kulu-Ya-Ku and earned 500 Zenny as a reward!" << endl;
        uinfo.userzenny += 500; // Reward the player with 500 Zenny for winning the battle
    }
    system("pause");
    system("cls");
}

void arena (userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu) {
	cout << "\t\t\t\t\t\tYou are entering the arena, please wait..." << endl;
	system("pause");
	system("cls");
	int choice;
	
	ifstream inFile("userdata.txt");

    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt" << endl;
        return;
    }
    
    // Read user data line by line from the file
    getline(inFile, uinfo.username);
    inFile >> uinfo.userzenny;
    inFile.ignore(); // Ignore the newline character after userzenny
    getline(inFile, uinfo.equippedGS);
    inFile >> uinfo.equippedGSdmg;
    inFile >> uinfo.healthpots;
    inFile.close();
	
	do {
		
		cout << "\t\t\t\t\t\tWelcome to the Arena warrior [" << uinfo.username << "]!" << endl;
        cout << "\t\t\t\t\t\tEquipped Great Sword: " << uinfo.equippedGS << endl;
		cout << "\t\t\t\t\t\tDamage: " << uinfo.equippedGSdmg << endl;
        cout << "\t\t\t\t\t\tHealth potions: " << uinfo.healthpots << endl;
		
		for (int i=0;i<120;i++){
			cout << "=";
		}
		
		cout << "\n\n\t\t\t\t\t       [============" << endl;
        cout << "\t\t\t\t\t\tBattle Center" << endl;
        cout << "\t\t\t\t\t        ============]\n" << endl;
        cout << "\t\t\t\t\t\t1. Kulu-Ya-Ku" << endl;
        cout << "\t\t\t\t\t\tReward: 500 Zenny\n" << endl;
        cout << "\t\t\t\t\t\t2. Barroth" << endl;
        cout << "\t\t\t\t\t\tReward: 750 Zenny\n" << endl;
        cout << "\t\t\t\t\t\t3. Diablos" << endl;
        cout << "\t\t\t\t\t\tReward: 1000 Zenny\n" << endl;
        cout << "\t\t\t\t\t\t4. Leave Arena" << endl;
        cout << "\n\t\t\t\t\t\tChoose a monster to fight or leave the arena: ";
        cin >> choice;
        
        switch (choice) {
        	case 1:
        		battlekulu(uinfo, kulu);
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
        		break;
        	default:
        		system("cls");
            	cout << "\t\t\t\t\tInvalid Input!!!";
            	break;
		}
        
	} while (choice != 4);
}

void mainmenu (userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu) {
	system("cls");
	int choice;
	
	do {
		
		cout << "\n\t\t\t\t\t       [============" << endl;
        cout << "\t\t\t\t\t\tMain Menu" << endl;
        cout << "\t\t\t\t\t        ============]\n" << endl;
        cout << "\t\t\t\t\t\t1. Colosseum Store" << endl;
        cout << "\t\t\t\t\t\t2. Enter Arena" << endl;
        cout << "\t\t\t\t\t\t3. Help(?)" << endl;
        cout << "\t\t\t\t\t\t4. Logout" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
        	case 1:
        		system("cls");
        		store(uinfo, buster, deathscythe, hellsplitter);
        		break;
        	case 2:
        		arena(uinfo, buster, deathscythe, hellsplitter, kulu);
        		break;
        	case 3:
        		break;
        	case 4:
        		system("cls");
        		break;
        	default:
        		system("cls");
            	cout << "\t\t\t\t\t\tInvalid Input!!!";
            	break;
		}
        
	} while (choice != 4);
}

void save(const userinfo &uinfo) {
    ofstream outFile("userdata.txt");

    if (outFile.is_open()) {
        outFile << uinfo.username << endl;
        outFile << uinfo.userzenny << endl;
        outFile << uinfo.equippedGS << endl;
        outFile << uinfo.equippedGSdmg << endl;
        outFile << uinfo.healthpots << endl;

        cout << "Game saved successfully!" << endl;
        outFile.close();
    } else {
        cout << "Error saving game data to userdata.txt" << endl;
    }
}
