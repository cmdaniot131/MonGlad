#include <iostream>
#include <cstdlib>
#include <fstream>
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
void ulog(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster &dummy);
void tutorial(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster &dummy);
void store(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &bar, monster &dia);
void battlekulu(userinfo &uinfo, monster &kulu);
void battlebarr(userinfo &uinfo, monster &bar);
void battledia(userinfo &uinfo, monster &dia);
void arena(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia);
void mainmenu(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster &dummy);
void save(const userinfo &uinfo);

int main() {
	
	userinfo uinfo;
	weapon buster = {"Buster Sword", 50}; 
	weapon deathscythe = {"Death Scythe", 80};
	weapon hellsplitter = {"Hell Splitter", 140};
	monster dummy = {"Dummy"};
	monster kulu = {"Kulu-Ya-Ku"};
	monster bar = {"Barroth"};
	monster dia = {"Diablos"};

	char choice;
	createFile();
	
	do {
        
		printf(
		    "\n\n\t\t\t  _     ___   ____ ___ _   _   ______   ______ _____ _____ __  __\n"
		    "\t\t\t | |   / _ \\ / ___|_ _| \\ | | / ___\\ \\ / / ___|_   _| ____|  \\/  |\n"
		    "\t\t\t | |  | | | | |  _ | ||  \\| | \\___ \\\\ V /\\___ \\ | | |  _| | |\\/| |\n"
		    "\t\t\t | |__| |_| | |_| || || |\\  |  ___) || |  ___) || | | |___| |  | |\n"
		    "\t\t\t |_____\\___/ \\____|___|_| \\_| |____/ |_| |____/ |_| |_____|_|  |_|\n"
		);
        
        cout << "\n\t\t\t\t\t\t[R]egister" << endl;
        cout << "\t\t\t\t\t\t[L]ogin" << endl;
        cout << "\t\t\t\t\t\t[E]xit" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();
		
		switch (choice) {
			case 'R':
			case 'r':
				system("cls");
				cout << "\n\n\t\tCreating a new user will overwrite the current stored data (1 Account Creation per game only)\n\n" << endl;
    			cout << "\t\t\t\t\t\t[B]ack to Login\n";
		        cout << "\t\t\t\t\t\t[C]ontinue Registration\n";
		        cout << "\t\t\t\t\t\tEnter your choice: ";
		        cin >> choice;
		        cin.ignore();
		        if (choice == 'B' || choice == 'b') {
		        	system("cls");
				} else if (choice == 'C' || choice == 'c') {
					ureg(uinfo, buster);
					system("cls");
				} else {
					system("cls");
					cout << "\t\t\t\t\t\tInvalid Input!!!";
				}
				break;
			case 'L':
			case 'l':
				ulog(uinfo, buster, deathscythe, hellsplitter, kulu, bar, dia, dummy);
				break;
			case 'E':
			case 'e':
				cout << "\t\t\t\t\t\tExiting game...";
                system("cls");
                break;
            default:
            	system("cls");
            	cout << "\t\t\t\t\t\tInvalid Input!!!";
            	break;
		}
		
	} while (choice != 'E' && choice != 'e');
	
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
    
    cout << "\n\t\t\t\t\t\tEnter New Username (Up to 5 characters only): ";
    getline(cin, newUser.username);
    
    int l = 0;
    while (newUser.username[l] != '\0') {
        l++;
    }
    
    if (l > 5) {
        cout << "\n\t\t\t\t\t\tInvalid input. Username should be up to 5 characters only." << endl;
        system("pause");
        system("cls");
        return;
    }
    
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
        ofstream outFile("userdata.txt");
        newUser.equippedGS = buster.name;
        newUser.equippedGSdmg = buster.damage;
        newUser.userzenny = 0;
        newUser.healthpots = 5;
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

void ulog(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster  &dummy) {
    ifstream inFile("userdata.txt");
    
    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt";
    } else {
        string storedusername;
        string uinput;
        bool existingUser = false;
        
        cout << "\n\t\t\t\t\t\tEnter Username: ";
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
            mainmenu(uinfo, buster, deathscythe, hellsplitter, kulu, bar, dia, dummy);
        }
    }
}

void tutorial(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster &dummy) {
	char choice;
    int phealth = 200;
    int mhealth = 100;
    int dmg;
	
	
	ifstream inFile("userdata.txt");
	if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt" << endl;
        return;
    }
    
    getline(inFile, uinfo.username);
    inFile >> uinfo.userzenny;
    inFile.ignore();
    getline(inFile, uinfo.equippedGS);
    inFile >> uinfo.equippedGSdmg;
    inFile >> uinfo.healthpots;
    inFile.close();

    cout << "Welcome the Monsters & Gladiators warrior [" << uinfo.username << "]!" << endl;
    cout << "In this tutorial, you will face a Dummy" << endl;
    cout << "\nYour goal is to defeat the monster while managing your health." << endl;
    cout << "\nYou can attack the monster and use health potions to restore your health." << endl;
	cout << "NOTE: New users receive 5 free potions when registering a new user" << endl;
    cout << "\nBe careful! The monster can also attack you." << endl << endl;
    cout << "Game Controls:" << endl;
    cout << "- Enter 'A' or 'a' to attack the monster." << endl;
    cout << "- Enter 'H' to 'h' use a health potion." << endl;
    cout << "- NOTE: Your health is limited to 200 points." << endl;
    cout << "- NOTE: You have a limited number of 10 health potions only." << endl << endl;
    cout << "Now go practice with that Dummy warrior [" << uinfo.username << "]!" << endl << endl;
    system("pause");
    system("cls");
	
    while (phealth > 0 && mhealth > 0) {
           
        cout << "\t\t\t\t        %%%%%%%           \n"
		     << "\t\t\t\t     %%%=====*#%%%        \n"
		     << "\t\t\t\t    %%*-:::::==*%%        \n"
		     << "\t\t\t\t    %%#+:::=*--=%%        \n"
		     << "\t\t\t\t    %%#*::-+*--=%%        \n"
		     << "\t\t\t\t    %%*=-----==+%%        \n"
		     << "\t\t\t\t      %%==---+*%**%%      \n"
		     << "\t\t\t\t    %%#*%%%%%%#*++=*%%    \n"
		     << "\t\t\t\t   %%*++**+**+*%**-=+#%   \n"
		     << "\t\t\t\t %%%#+*#++====++%%---*#%% \n"
		     << "\t\t\t\t %%*+-*%--+=--=+%%--:=+%% \n"
		     << "\t\t\t\t %%+--*%::+=--=+%%#+:-=%% \n"
		     << "\t\t\t\t %%=:-*%::---==+%%%#+=+%% \n"
		     << "\t\t\t\t   %%%%%**#+-++*%% %%%%   \n"
		     << "\t\t\t\t        %%*++*#%%         \n"
		     << "\t\t\t\t         %%%%%%           \n"
		     << "\t\t\t\t         %%%#%%           \n"
		     << "\t\t\t\t         %%#*%%           \n"
		     << "\t\t\t\t   %%%%%%%####%%%%%%%%    \n"
		     << "\t\t\t\t %%*+*******+*****##*%%   \n"
		     << "\t\t\t\t %%##################%%   \n";    
           
    	cout << "\n\t\t\t\t\tDummy Health: " << mhealth << endl;
    	cout << endl;
    	
    	for (int i=0;i<120;i++){
			cout << "*";
		}
    	
    	cout << endl;
        cout << "\n\t\t\t\t\t\tYour Health: " << phealth << endl;
        cout << "\t\t\t\t\t\t[A]ttack" << endl;
        cout << "\t\t\t\t\t\tUse [H]ealth Potion (Remaining: " << uinfo.healthpots << ")" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'A':
            case 'a':
                if (rand() % 2 == 0) {
                    dmg = rand() % uinfo.equippedGSdmg + 1;
                    mhealth -= dmg;
                    cout << "\n\t\t\t\t\t\tYou dealt " << dmg << " damage to Dummy!" << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYour attack missed!" << endl;
                }
                break;
            case 'H':
			case 'h':
			    if (uinfo.healthpots > 0) {
			        if (phealth < 200) {
			            phealth += 50;
			            if (phealth > 200) {
			                phealth = 200;
			            }
			            uinfo.healthpots--;
			            cout << "\n\t\t\t\t\t\tYou used a health potion. Restored 50 health points." << endl;
			        } else {
			            cout << "\n\t\t\t\t\t\tYour health is already at its maximum. You don't need to use a health potion." << endl;
			        }
			    } else {
			        cout << "\n\t\t\t\t\t\tYou don't have any health potions left!" << endl;
			    }
                break;
            default:
                cout << "\n\t\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        
        if (rand() % 2 == 0) {
            dmg = rand() % 15 + 1;
            phealth -= dmg;
            cout << "\n\t\t\t\t\t\tDummy dealt " << dmg << " damage to you!" << endl;
        } else {
            cout << "\n\t\t\t\t\t\tDummy's attack missed!" << endl;
        }

        system("pause");
        system("cls");
    }

    if (phealth <= 0) {
        cout << "\n\t\t\tYou were defeated by a Dummy. Do better!" << endl;
    } else {
        cout << "\n\t\tCongratulations for completing the tutorial! Now go defeat some real beasts!" << endl;
        uinfo.userzenny += 0;
    }
    system("pause");
    system("cls");
    mainmenu(uinfo, buster, deathscythe, hellsplitter, kulu, bar, dia, dummy);
}

void store(userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter) {
    system("cls");
    char choice;
    
    ifstream inFile("userdata.txt");

    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt" << endl;
        return;
    }
    inFile.close();

    do {
        cout << "\n\t\t\t\t\t------------ Colosseum Store ------------" << endl;
        cout << "\t\t\t\t\tCurrent Zenny: " << uinfo.userzenny << endl;
        cout << "\n\t\t\t\t\t[1] Buy Health Potion (300 Zenny)" << endl;
		printf("\t\t\t\t\t.-----------------------------.\n"
	           "\t\t\t\t\t.###############################.\n"
	           "\t\t\t\t\t.##+----+####+------####+----+##.\n"
	           "\t\t\t\t\t.#####+-+##---+####---##+-+#####.\n"
	           "\t\t\t\t\t...-##-+##--###-+#+--##+-+#-...\n"
	           "\t\t\t\t\t-###-+##--+#+-----+##+-+##-\n"
	           "\t\t\t\t\t-###+--+###---##+++####+--+###-\n"
	           "\t\t\t\t\t+##--+#######--+#########+--##+\n"
	           "\t\t\t\t\t+##--#########+--#########--##+\n"
	           "\t\t\t\t\t+##--##########--#########--##+\n"
	           "\t\t\t\t\t+##--#####################--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--##+---------------+##--##+\n"
	           "\t\t\t\t\t+##--#####################--##+\n"
	           "\t\t\t\t\t+##----+++++++++++++++++----##+\n"
	           "\t\t\t\t\t+###+---------------------+###+\n"
	           "\t\t\t\t\t..###########################.\n");
	           
        cout << "\n\t\t\t\t\t[2] Buy Death Scythe (1500 Zenny)" << endl;
        printf("\t\t\t\t\t                                                  \n"
           "\t\t\t\t\t                $$$XXX++                          \n"
           "\t\t\t\t\t        &&&&&$$$$$$XXXXXxx                        \n"
           "\t\t\t\t\t   &&&$&&&&&$&&$$XXxXXxX                          \n"
           "\t\t\t\t\t&&&$$$$XXXXX$X$$XXxXXxxx                          \n"
           "\t\t\t\t\t&$                 $$XxXXX                        \n"
           "\t\t\t\t\t                  $$XXXxxxx                       \n"
           "\t\t\t\t\t                    X  XXXxxx$                    \n"
           "\t\t\t\t\t                     $$$xXXXxxX                   \n"
           "\t\t\t\t\t                        $$XXXXXxXx                \n"
           "\t\t\t\t\t                          XXXxXxXx                \n"
           "\t\t\t\t\t                           X$Xx+xx                \n"
           "\t\t\t\t\t                            XXXXxxx               \n"
           "\t\t\t\t\t                              Xx; $xx             \n"
           "\t\t\t\t\t                                 XxX$xx           \n"
           "\t\t\t\t\t                                      XX          \n"
           "\t\t\t\t\t                                        Xx        \n");
           
        cout << "\n\t\t\t\t\t[3] Buy Hell Splitter (3000 Zenny)" << endl;
		printf("\t\t\t\t\t               \n"
           "\t\t\t\t\t                   X                              \n"
           "\t\t\t\t\t                   x+x                            \n"
           "\t\t\t\t\t    .               X+;+                          \n"
           "\t\t\t\t\t    +x:             &$X;;+                        \n"
           "\t\t\t\t\t    :$$x;.          &&&$x;;                       \n"
           "\t\t\t\t\t    .X$$&$x;:.   & &&&&&$X;;                      \n"
           "\t\t\t\t\t     ;$$$$&&$&&&&&$$$&&&&&$++                     \n"
           "\t\t\t\t\t      +$$&&&&&&&&&&$X$&&&&&$+X                    \n"
           "\t\t\t\t\t       ;$$&&&&&&&&&$&$$&&&&&xx                    \n"
           "\t\t\t\t\t       .:X&&&&&&&&&&&&&$$&&&&xX                   \n"
           "\t\t\t\t\t         .+$&&&&&&&&&&&&&$$&&XX                   \n"
           "\t\t\t\t\t           .x$&&&&&&&&&&&&&&$$X$                  \n"
           "\t\t\t\t\t             ;$$&&&&&&&&&&&$&&$$                  \n"
           "\t\t\t\t\t                $$&&&&&&&&&&&&$&$&&&              \n"
           "\t\t\t\t\t                  &$&&&&&&&&&$&&&$$&              \n"
           "\t\t\t\t\t                     $$&&&&&&&&&&&$$              \n"
           "\t\t\t\t\t                       &$&&&&&&& &&&$             \n"
           "\t\t\t\t\t                         &$&&&&$&&&&&&&           \n"
           "\t\t\t\t\t                            $&&&&&& &&&&          \n"
           "\t\t\t\t\t                               &&&&&  &&&&        \n"
           "\t\t\t\t\t                                 &&&&   &&&       \n"
           "\t\t\t\t\t                                   $&&    &&&     \n"
           "\t\t\t\t\t                                    $&     &&&    \n"
           "\t\t\t\t\t                                           &&&    \n");
        
        cout << "\t\t\t\t\t[4] Leave Colosseum Store" << endl << endl;
        
        cout << "\t\t\t\t\tCurrent Zenny: " << uinfo.userzenny << endl;
        
        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                system("cls");
                if (uinfo.userzenny >= 300 && uinfo.healthpots < 10) {
                	uinfo.userzenny -= 300;
                	uinfo.healthpots++;
                	system("cls");
                	cout << "\t\t\t\t\tYou have purchased a health potion! Current Health Potions: " << uinfo.healthpots << endl;
                	system("pause");
                	save(uinfo);
				} else if (uinfo.healthpots >= 10) {
					cout << "\t\t\t\t\tYou cannot buy more health potions. You already have the maximum limit (10)." << endl;
				} else {
					cout << "\t\t\t\t\tNot enough Zenny to buy a health potion. Go win some battles first!" << endl;
				}
				system("pause");
                break;
            case '2':
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
            case '3':
                system("cls");
			    if (uinfo.userzenny >= 3000 && uinfo.equippedGS != hellsplitter.name) {
			        uinfo.userzenny -= 3000;
			        uinfo.equippedGS = hellsplitter.name;
			        uinfo.equippedGSdmg = hellsplitter.damage;
			        cout << "\t\t\t\t\tYou have purchased Hell Splitter! Current Equipped Weapon: " << uinfo.equippedGS << endl;
			        save(uinfo);
			    } else if (uinfo.equippedGS == hellsplitter.name) {
			        cout << "\t\t\t\t\tYou already have this item!" << endl;
			    } else {
			        cout << "\t\t\t\t\tNot enough Zenny to buy Hell Splitter. Go win some battles first!" << endl;
			    }
			    system("pause");
                break;
            case '4':
            	system("cls");
            	break;
            default:
            	system("cls");
                cout << "\t\t\t\t\tInvalid Input!!!";
                break;
        }
        
    } while (choice != '4');
}

void battlekulu(userinfo &uinfo, monster &kulu) {
	char choice;
    int phealth = 200;
    int mhealth = 250;
    int dmg;

    system("cls");
    cout << "\n\t\t\t\t\tPrepare for battle! You are facing a Kulu-Ya-Ku." << endl;
    system("pause");
    system("cls");

    while (phealth > 0 && mhealth > 0) {
    	
    	printf("\t\t\t\t                     X xx      \n"
           "\t\t\t\t                    XXXXx      \n"
           "\t\t\t\t                    XXXxx      \n"
           "\t\t\t\t                    Xxxx+;;    \n"
           "\t\t\t\t                    Xx+;xx+xXXX\n"
           "\t\t\t\t                    xxxxxX$XX  \n"
           "\t\t\t\t                    xX$XXx++x  \n"
           "\t\t\t\t                   xxXX$X xX$$ \n"
           "\t\t\t\t $$                xxxX        \n"
           "\t\t\t\t $$              $x+++x        \n"
           "\t\t\t\t $$         X$$X$x+:;;;        \n"
           "\t\t\t\t XX       XxX$xxxx;;+++x;;     \n"
           "\t\t\t\t +;;     x+;:+xx+;xXXXxxx;;    \n"
           "\t\t\t\t x;:;  xxx+:+XXx+++xxxXxXxx    \n"
           "\t\t\t\t xxx+xXXxx+:+xxxxxX$$xXXXXX    \n"
           "\t\t\t\t   xxxxxxx+:xxX   XXX$$XXXX    \n"
           "\t\t\t\t         xxx    XXXX   XX      \n"
           "\t\t\t\t        xxx      XXX+          \n"
           "\t\t\t\t       XXx         XXXx$       \n"
           "\t\t\t\t       xX            $XX$$     \n"
           "\t\t\t\t      x++X$                    \n"
           "\t\t\t\t     $XX$                     \n");
    	cout << "\n\t\t\t\t\tKulu-Ya-Ku's Health: " << mhealth << endl;
    	cout << endl;
    	
    	for (int i=0;i<120;i++){
			cout << "*";
		}
    	
    	cout << endl;
        cout << "\n\t\t\t\t\t\tYour Health: " << phealth << endl;
        cout << "\t\t\t\t\t\t[A]ttack" << endl;
        cout << "\t\t\t\t\t\tUse [H]ealth Potion (Remaining: " << uinfo.healthpots << ")" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'A':
            case 'a':
                if (rand() % 2 == 0) {
                    dmg = rand() % uinfo.equippedGSdmg + 1;
                    mhealth -= dmg;
                    cout << "\n\t\t\t\t\t\tYou dealt " << dmg << " damage to Kulu-Ya-Ku!" << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYour attack missed!" << endl;
                }
                break;
            case 'H':
			case 'h':
			    if (uinfo.healthpots > 0) {
			        if (phealth < 200) {
			            phealth += 50;
			            if (phealth > 200) {
			                phealth = 200;
			            }
			            uinfo.healthpots--;
			            cout << "\n\t\t\t\t\t\tYou used a health potion. Restored 50 health points." << endl;
			        } else {
			            cout << "\n\t\t\t\t\t\tYour health is already at its maximum. You don't need to use a health potion." << endl;
			        }
			    } else {
			        cout << "\n\t\t\t\t\t\tYou don't have any health potions left!" << endl;
			    }
                break;
            default:
                cout << "\n\t\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        
        if (rand() % 2 == 0) {
            dmg = rand() % 30 + 1;
            phealth -= dmg;
            cout << "\n\t\t\t\t\t\tKulu-Ya-Ku dealt " << dmg << " damage to you!" << endl;
        } else {
            cout << "\n\t\t\t\t\t\tKulu-Ya-Ku's attack missed!" << endl;
        }

        system("pause");
        system("cls");
    }

    if (phealth <= 0) {
        cout << "\n\t\t\tYou were defeated by Kulu-Ya-Ku. Better luck next time!" << endl;
    } else {
        cout << "\n\t\t\tMONSTER CLEARED! You defeated Kulu-Ya-Ku and earned 600 Zenny as a reward!" << endl;
        uinfo.userzenny += 600;
        save(uinfo);
    }
    system("pause");
    system("cls");
}

void battlebarr(userinfo &uinfo, monster &bar) {
	char choice;
    int phealth = 200;
    int mhealth = 450;
    int dmg;

    system("cls");
    cout << "\n\t\t\t\t\tPrepare for battle! You are facing a Barroth." << endl;
    system("pause");
    system("cls");

    while (phealth > 0 && mhealth > 0) {
    	
    	printf("\n\t\t\t\t           ;x+:                                    \n"
           "\t\t\t\t    .:x+;:.:xX:   :;;;;xx+:xX                      \n"
           "\t\t\t\t    .:$$$$$$;+x;;x++x;;xx:xxxxxxxXX                \n"
           "\t\t\t\t    .:Xx+;::;;;:;+;+x;+xx:xxxxxxxxxx XXX           \n"
           "\t\t\t\t         :+$X;        :::::+xxxxxxxxxXXXX          \n"
           "\t\t\t\t      :::;X$x:                xxxxXxxxXXXxxxxxxxxxX\n"
           "\t\t\t\t    :+xx;                      xxxxxxxXxx+xxXxxX$$$\n"
           "\t\t\t\t      ::               :xXx;  xxxxxxxXxxxxxxxxxxXX$\n"
           "\t\t\t\t       :;xX+:          ;XXXx  xxxxxxxxxxxxxxxxxxXX$\n"
           "\t\t\t\t       :xx+xx     :+;        xxxxxxXxXxxxxxxxxxX$$$\n"
           "\t\t\t\t        :xX+:     ;x+        xxxxxxxxXXxxxxxxxxX$$$\n"
           "\t\t\t\t  XxxxXXx                    xxxxxxxxxXxxxxxxxxx   \n"
           "\t\t\t\t xxXxxxXxx xxxxxXx   Xxx     xXXxxxxxxxxxxxxxxx    \n"
           "\t\t\t\t xxXxxxXxxxxxxxxxXxxxXXxXX  XxxxxxxxxxXXXXXXXX     \n"
           "\t\t\t\t  xxXxxxXxxxxxXxxXxxxxXxXxxxxXxxxxxxXXXXXXXXXX     \n"
           "\t\t\t\t  xxxXxxXxxxxxXxxXxxxxXxXxxXxxXxxxxxXXXXX$XXX      \n"
           "\t\t\t\t   xxxxxxXxxxxxxxXxxxxXxXxxXxxx+xxxxXXXXXXXXX      \n"
           "\t\t\t\t    xxxxxXxxxxxxxxxxxxxxXxxxxxxxxxxxxxxXXXXXX      \n"
           "\t\t\t\t xx xxxxxxXxxxxxxxxxxxxxxxxxxxxXxxxxxxxxxx         \n"
           "\t\t\t\t xxx  xxxxxxxxxxxxxxxxxxXxxxxXXXXxxxXxxxx          \n"
           "\t\t\t\t      xxxxxxxxxxXxxxxxxxxxxXXXXXXXXxxxxxxxx        \n"
           "\t\t\t\t       xxxxxxxxxxxxxxxxxxxXXXXX$XXXxxxxX$$$        \n"
           "\t\t\t\t $$XX$$ xxxxxxxxxxxxX++xXXXXXXXXX xxxxX$$$         \n"
           "\t\t\t\t $Xxx$$ XXx+xXx+xXxxX+xxXXXXXXX     X$$$$          \n"
           "\t\t\t\t   $$  XXXXXXXXXXXXXXXXXXXXX                       \n"
           "\t\t\t\t      XXXXXXXXXXXXXXXXXXX                          \n");
    	
        cout << "\n\t\t\t\t\tBarroth's Health: " << mhealth << endl;
        cout << endl;
    	
    	for (int i=0;i<120;i++){
			cout << "*";
		}
    	
    	cout << endl;
        cout << "\n\n\t\t\t\t\t\tYour Health: " << phealth << endl;
        cout << "\t\t\t\t\t\t[A]ttack" << endl;
        cout << "\t\t\t\t\t\tUse [H]ealth Potion (Remaining: " << uinfo.healthpots << ")" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'A':
            case 'a':
                if (rand() % 2 == 0) {
                    dmg = rand() % uinfo.equippedGSdmg + 1;
                    mhealth -= dmg;
                    cout << "\n\t\t\t\t\t\tYou dealt " << dmg << " damage to Barroth!" << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYour attack missed!" << endl;
                }
                break;
            case 'H':
            case 'h':
                if (uinfo.healthpots > 0) {
			        if (phealth < 200) {
			            phealth += 50;
			            if (phealth > 200) {
			                phealth = 200;
			            }
			            uinfo.healthpots--;
			            cout << "\n\t\t\t\t\t\tYou used a health potion. Restored 50 health points." << endl;
			        } else {
			            cout << "\n\t\t\t\t\t\tYour health is already at its maximum. You don't need to use a health potion." << endl;
			        }
			    } else {
			        cout << "\n\t\t\t\t\t\tYou don't have any health potions left!" << endl;
			    }
                break;
            default:
                cout << "\n\t\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        if (rand() % 2 == 0) {
            dmg = rand() % 50 + 1;
            phealth -= dmg;
            cout << "\n\t\t\t\t\t\tBarroth dealt " << dmg << " damage to you!" << endl;
        } else {
            cout << "\n\t\t\t\t\t\tBarroth's attack missed!" << endl;
        }

        system("pause");
        system("cls");
    }

    if (phealth <= 0) {
        cout << "\n\t\t\tYou were defeated by Barroth. Better luck next time!" << endl;
    } else {
        cout << "\n\t\t\tMONSTER CLEARED! You defeated Barroth and earned 750 Zenny as a reward!" << endl;
        uinfo.userzenny += 750;
        save(uinfo);
    }
    system("pause");
    system("cls");
}

void battledia(userinfo &uinfo, monster &dia) {
	char choice;
    int phealth = 200;
    int mhealth = 650;
    int dmg;

    system("cls");
    cout << "\n\t\t\t\t\tPrepare for battle! You are facing Diablos." << endl;
    system("pause");
    system("cls");

    while (phealth > 0 && mhealth > 0) {
    	
    	printf(
        "\n\t\t\t\t         $$$&$$$$$$            &&&&&&&&                \n"
        "\t\t\t\t      $$$$$$$$$$$$$$&    &&&$$$$$$$$$$$$&&             \n"
        "\t\t\t\t   $$&$$$$$$$$$$&$$$$&&$$$$$$$$$$$$$$$$$$$$$&&         \n"
        "\t\t\t\t   $$$$$$$$$$&&&&&$$$$$$$$$$$$$$$$$$$$$$$$$$$$$&       \n"
        "\t\t\t\t    &$$$$$&&&&&&&$$$$$$$$$$&  $$$&$$$$$$$$$$$$$$$      \n"
        "\t\t\t\t       &$  $$$$$$$&&$$$               $$$$$$$$$$$&     \n"
        "\t\t\t\t    &$$$$$$&&&&&&&&&$$$               &$$$$$$$$$&&&    \n"
        "\t\t\t\t   &$$$$$$$$$&&&&$$$$$$&&       && $$$$$$$$$$$$$$&&    \n"
        "\t\t\t\t    $$$&$$$$$$$$$$$$$&&&&&$$$$&&&&&$$$$$$$$$$$$&$$$    \n"
        "\t\t\t\t  $$$$$$$$$$$$$$$$$$&&&&&&&$$&&&&&&$$$$$$$$$$$$&&$$$$  \n"
        "\t\t\t\t $$$$ &$&  $$$$&&&&$&&&&$$$$$$$&&&&&$&&&$$$$$$$   $$$$$\n"
        "\t\t\t\t$$$$$  $$$ $$& &&&&$$$$$$$$$$$$$$$$$&&&&$$$$$$$$  $$$$$\n"
        "\t\t\t\t$$$$$ $$$$   &$$&&$$$$$$$$$$$$$$$$$$$&&&$$$$$$$$$ $$$$$\n"
        "\t\t\t\t$$$$$$$$$$$  &&&&$$$$$$$$$$$X$$$$$$$$$$$&&&&$&$$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$   $&&$$$$$$$$$$$$$$$$$$$$$$$$$&&&$&&$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$& &$$$$$$&&&&&&&$$$$$&&&&&&&&$$$$$$&&$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$$$$$$$&&&&&&&&&&&&$&&&&&&&&&&&&$ &$$$$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$$$$$&&&&&&&&&&&&&&$&&&&&&&&&&&&&&$$$$$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$\n"
        "\t\t\t\t$$$$$$$$$$$$$&&&&&&&&&&&&&&&$&&&&&&&&&&&&&&&$$$$$$$$$$$$\n"
        "\t\t\t\t $$$$$$$$$$&&&&&&&&&&&&&&&$$$&&&&&&&&&&&&&&&$$$$$$$$$$ \n"
        "\t\t\t\t $$$$$$$$$$$&&&&&&&&&$$$$$$$$$$$$$&&&&&&&&&$$$$$$$$$$& \n"
        "\t\t\t\t  $$$$$$$$$$&&&&&&&&&$$$$$$$$$$$$$&&&&&&&&&$$$$$$$$$$  \n"
        "\t\t\t\t   $$$$$$$$$$&&&&&&$$&&&$$$$$$$&&&$$&&&&&&$$$$$$$$$$   \n"
        "\t\t\t\t    $$$$$$$$$&&&&&&&$&&&&$$$$$&&&&$&&&&&&&$$$$$$$$$    \n"
        "\t\t\t\t  &$$$$$$$$$$$&&&&&&&&&&&&&&$&&&&&&&&&&&&$$$$$$$$$$$&  \n"
        "\t\t\t\t  &$$$$$$$$$$$$  &&&&&&&&&&&&&&&&&&&&&& &$$$$$$$$$$$&  \n"
        "\t\t\t\t  &&&&&&&&&&&&&    &&&&&&&   &&&&&&&    &&&&&&&&&&&&&  \n"
        "\t\t\t\t &&&&&&&&&&&&&&&    &&&&       &&&&     &&&&&&&&&&&&&& \n"
        "\t\t\t\t  &&&&&&&&&&&&&     &&&         &&&     &&&&&&&&&&&&&  \n"
    );
    	
        cout << "\n\t\t\t\t\tDiablos Health: " << mhealth << endl;
        cout << endl;
    	
    	for (int i=0;i<120;i++){
			cout << "*";
		}
    	
    	cout << endl;
        cout << "\n\n\t\t\t\t\t\tYour Health: " << phealth << endl;
        cout << "\t\t\t\t\t\t[A]ttack" << endl;
        cout << "\t\t\t\t\t\tUse [H]ealth Potion (Remaining: " << uinfo.healthpots << ")" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'A':
            case 'a':
                if (rand() % 2 == 0) {
                    dmg = rand() % uinfo.equippedGSdmg + 1;
                    mhealth -= dmg;
                    cout << "\n\t\t\t\t\t\tYou dealt " << dmg << " damage to Diablos!" << endl;
                } else {
                    cout << "\n\t\t\t\t\t\tYour attack missed!" << endl;
                }
                break;
            case 'H':
            case 'h':
                if (uinfo.healthpots > 0) {
			        if (phealth < 200) {
			            phealth += 50;
			            if (phealth > 200) {
			                phealth = 200;
			            }
			            uinfo.healthpots--;
			            cout << "\n\t\t\t\t\t\tYou used a health potion. Restored 50 health points." << endl;
			        } else {
			            cout << "\n\t\t\t\t\t\tYour health is already at its maximum. You don't need to use a health potion." << endl;
			        }
			    } else {
			        cout << "\n\t\t\t\t\t\tYou don't have any health potions left!" << endl;
			    }
                break;
            default:
                cout << "\n\t\t\t\t\t\tInvalid choice! Try again." << endl;
                break;
        }

        
        if (rand() % 2 == 0) {
            dmg = rand() % 65 + 1;
            phealth -= dmg;
            cout << "\n\t\t\t\t\t\tDiablos dealt " << dmg << " damage to you!" << endl;
        } else {
            cout << "\n\t\t\t\t\t\tAttack of Diablos missed!" << endl;
        }

        system("pause");
        system("cls");
    }

    if (phealth <= 0) {
        cout << "\n\t\t\tYou were defeated by Diablos. Better luck next time!" << endl;
    } else {
        cout << "\n\t\t\tMONSTER CLEARED! You have defeated Diablos and earned 1000 Zenny as a reward!" << endl;
        uinfo.userzenny += 1000;
        save(uinfo);
    }
    system("pause");
    system("cls");
}

void arena (userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia) {
	cout << "\t\t\t\t\t\tYou are entering the arena, please wait..." << endl;
	system("pause");
	system("cls");
	char choice;
	
	ifstream inFile("userdata.txt");

    if (!inFile.is_open()) {
        cout << "Unable to find userdata.txt" << endl;
        return;
    }
    
    getline(inFile, uinfo.username);
    inFile >> uinfo.userzenny;
    inFile.ignore();
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
        
        printf("\t\t\t\t\t                     X xx      \n"
           "\t\t\t\t\t                    XXXXx      \n"
           "\t\t\t\t\t                    XXXxx      \n"
           "\t\t\t\t\t                    Xxxx+;;    \n"
           "\t\t\t\t\t                    Xx+;xx+xXXX\n"
           "\t\t\t\t\t                    xxxxxX$XX  \n"
           "\t\t\t\t\t                    xX$XXx++x  \n"
           "\t\t\t\t\t                   xxXX$X xX$$ \n"
           "\t\t\t\t\t $$                xxxX        \n"
           "\t\t\t\t\t $$              $x+++x        \n"
           "\t\t\t\t\t $$         X$$X$x+:;;;        \n"
           "\t\t\t\t\t XX       XxX$xxxx;;+++x;;     \n"
           "\t\t\t\t\t +;;     x+;:+xx+;xXXXxxx;;    \n"
           "\t\t\t\t\t x;:;  xxx+:+XXx+++xxxXxXxx    \n"
           "\t\t\t\t\t xxx+xXXxx+:+xxxxxX$$xXXXXX    \n"
           "\t\t\t\t\t   xxxxxxx+:xxX   XXX$$XXXX    \n"
           "\t\t\t\t\t         xxx    XXXX   XX      \n"
           "\t\t\t\t\t        xxx      XXX+          \n"
           "\t\t\t\t\t       XXx         XXXx$       \n"
           "\t\t\t\t\t       xX            $XX$$     \n"
           "\t\t\t\t\t      x++X$                    \n"
           "\t\t\t\t\t     $XX$                     \n");
	    
        cout << "\n\t\t\t\t\t\t[K]ulu-Ya-Ku" << endl;
        cout << "\t\t\t\t\t\tReward: 500 Zenny\n\n" << endl;
        
        for (int i=0;i<120;i++){
			cout << "-";
		}
        
        cout << endl;
        printf("\n\t\t\t\t\t           ;x+:                                    \n"
           "\t\t\t\t\t    .:x+;:.:xX:   :;;;;xx+:xX                      \n"
           "\t\t\t\t\t    .:$$$$$$;+x;;x++x;;xx:xxxxxxxXX                \n"
           "\t\t\t\t\t    .:Xx+;::;;;:;+;+x;+xx:xxxxxxxxxx XXX           \n"
           "\t\t\t\t\t         :+$X;        :::::+xxxxxxxxxXXXX          \n"
           "\t\t\t\t\t      :::;X$x:                xxxxXxxxXXXxxxxxxxxxX\n"
           "\t\t\t\t\t    :+xx;                      xxxxxxxXxx+xxXxxX$$$\n"
           "\t\t\t\t\t      ::               :xXx;  xxxxxxxXxxxxxxxxxxXX$\n"
           "\t\t\t\t\t       :;xX+:          ;XXXx  xxxxxxxxxxxxxxxxxxXX$\n"
           "\t\t\t\t\t       :xx+xx     :+;        xxxxxxXxXxxxxxxxxxX$$$\n"
           "\t\t\t\t\t        :xX+:     ;x+        xxxxxxxxXXxxxxxxxxX$$$\n"
           "\t\t\t\t\t  XxxxXXx                    xxxxxxxxxXxxxxxxxxx   \n"
           "\t\t\t\t\t xxXxxxXxx xxxxxXx   Xxx     xXXxxxxxxxxxxxxxxx    \n"
           "\t\t\t\t\t xxXxxxXxxxxxxxxxXxxxXXxXX  XxxxxxxxxxXXXXXXXX     \n"
           "\t\t\t\t\t  xxXxxxXxxxxxXxxXxxxxXxXxxxxXxxxxxxXXXXXXXXXX     \n"
           "\t\t\t\t\t  xxxXxxXxxxxxXxxXxxxxXxXxxXxxXxxxxxXXXXX$XXX      \n"
           "\t\t\t\t\t   xxxxxxXxxxxxxxXxxxxXxXxxXxxx+xxxxXXXXXXXXX      \n"
           "\t\t\t\t\t    xxxxxXxxxxxxxxxxxxxxXxxxxxxxxxxxxxxXXXXXX      \n"
           "\t\t\t\t\t xx xxxxxxXxxxxxxxxxxxxxxxxxxxxXxxxxxxxxxx         \n"
           "\t\t\t\t\t xxx  xxxxxxxxxxxxxxxxxxXxxxxXXXXxxxXxxxx          \n"
           "\t\t\t\t\t      xxxxxxxxxxXxxxxxxxxxxXXXXXXXXxxxxxxxx        \n"
           "\t\t\t\t\t       xxxxxxxxxxxxxxxxxxxXXXXX$XXXxxxxX$$$        \n"
           "\t\t\t\t\t $$XX$$ xxxxxxxxxxxxX++xXXXXXXXXX xxxxX$$$         \n"
           "\t\t\t\t\t $Xxx$$ XXx+xXx+xXxxX+xxXXXXXXX     X$$$$          \n"
           "\t\t\t\t\t   $$  XXXXXXXXXXXXXXXXXXXXX                       \n"
           "\t\t\t\t\t      XXXXXXXXXXXXXXXXXXX                          \n");
        
        cout << "\n\t\t\t\t\t\t[B]arroth" << endl;
        cout << "\t\t\t\t\t\tReward: 750 Zenny\n\n" << endl;
        
        for (int i=0;i<120;i++){
			cout << "-";
		}
        
        cout << endl;
        printf(
        "\n\t\t\t\t\t         $$$&$$$$$$            &&&&&&&&                \n"
        "\t\t\t\t\t      $$$$$$$$$$$$$$&    &&&$$$$$$$$$$$$&&             \n"
        "\t\t\t\t\t   $$&$$$$$$$$$$&$$$$&&$$$$$$$$$$$$$$$$$$$$$&&         \n"
        "\t\t\t\t\t   $$$$$$$$$$&&&&&$$$$$$$$$$$$$$$$$$$$$$$$$$$$$&       \n"
        "\t\t\t\t\t    &$$$$$&&&&&&&$$$$$$$$$$&  $$$&$$$$$$$$$$$$$$$      \n"
        "\t\t\t\t\t       &$  $$$$$$$&&$$$               $$$$$$$$$$$&     \n"
        "\t\t\t\t\t    &$$$$$$&&&&&&&&&$$$               &$$$$$$$$$&&&    \n"
        "\t\t\t\t\t   &$$$$$$$$$&&&&$$$$$$&&       && $$$$$$$$$$$$$$&&    \n"
        "\t\t\t\t\t    $$$&$$$$$$$$$$$$$&&&&&$$$$&&&&&$$$$$$$$$$$$&$$$    \n"
        "\t\t\t\t\t  $$$$$$$$$$$$$$$$$$&&&&&&&$$&&&&&&$$$$$$$$$$$$&&$$$$  \n"
        "\t\t\t\t\t $$$$ &$&  $$$$&&&&$&&&&$$$$$$$&&&&&$&&&$$$$$$$   $$$$$\n"
        "\t\t\t\t\t$$$$$  $$$ $$& &&&&$$$$$$$$$$$$$$$$$&&&&$$$$$$$$  $$$$$\n"
        "\t\t\t\t\t$$$$$ $$$$   &$$&&$$$$$$$$$$$$$$$$$$$&&&$$$$$$$$$ $$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$$  &&&&$$$$$$$$$$$X$$$$$$$$$$$&&&&$&$$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$   $&&$$$$$$$$$$$$$$$$$$$$$$$$$&&&$&&$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$& &$$$$$$&&&&&&&$$$$$&&&&&&&&$$$$$$&&$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$$$$$$$&&&&&&&&&&&&$&&&&&&&&&&&&$ &$$$$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$$$$$&&&&&&&&&&&&&&$&&&&&&&&&&&&&&$$$$$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$\n"
        "\t\t\t\t\t$$$$$$$$$$$$$&&&&&&&&&&&&&&&$&&&&&&&&&&&&&&&$$$$$$$$$$$$\n"
        "\t\t\t\t\t $$$$$$$$$$&&&&&&&&&&&&&&&$$$&&&&&&&&&&&&&&&$$$$$$$$$$ \n"
        "\t\t\t\t\t $$$$$$$$$$$&&&&&&&&&$$$$$$$$$$$$$&&&&&&&&&$$$$$$$$$$& \n"
        "\t\t\t\t\t  $$$$$$$$$$&&&&&&&&&$$$$$$$$$$$$$&&&&&&&&&$$$$$$$$$$  \n"
        "\t\t\t\t\t   $$$$$$$$$$&&&&&&$$&&&$$$$$$$&&&$$&&&&&&$$$$$$$$$$   \n"
        "\t\t\t\t\t    $$$$$$$$$&&&&&&&$&&&&$$$$$&&&&$&&&&&&&$$$$$$$$$    \n"
        "\t\t\t\t\t  &$$$$$$$$$$$&&&&&&&&&&&&&&$&&&&&&&&&&&&$$$$$$$$$$$&  \n"
        "\t\t\t\t\t  &$$$$$$$$$$$$  &&&&&&&&&&&&&&&&&&&&&& &$$$$$$$$$$$&  \n"
        "\t\t\t\t\t  &&&&&&&&&&&&&    &&&&&&&   &&&&&&&    &&&&&&&&&&&&&  \n"
        "\t\t\t\t\t &&&&&&&&&&&&&&&    &&&&       &&&&     &&&&&&&&&&&&&& \n"
        "\t\t\t\t\t  &&&&&&&&&&&&&     &&&         &&&     &&&&&&&&&&&&&  \n"
    );
        
        cout << "\n\t\t\t\t\t\t[D]iablos" << endl;
        cout << "\t\t\t\t\t\tReward: 1000 Zenny\n\n" << endl;

        cout << "\t\t\t\t\t\t[L]eave the Arena" << endl;
        cout << "\n\t\t\t\t\t\tChoose a monster to fight or leave the arena: ";
        cin >> choice;
        
        switch (choice) {
        	case 'K':
        	case 'k':
        		battlekulu(uinfo, kulu);
        		system("cls");
        		break;
        	case 'B':
        	case 'b':
        		battlebarr(uinfo, bar);
        		system("cls");
        		break;
        	case 'D':
        	case 'd':
        		battledia(uinfo, dia);
        		system("cls");
        		break;
        	case 'L':
        	case 'l':
        		system("cls");
        		break;
        	default:
        		system("cls");
            	cout << "\t\t\t\t\tInvalid Input!!!\n\n";
            	break;
		}
        
	} while (choice != 'L' && choice != 'l');
}

void mainmenu (userinfo &uinfo, weapon &buster, weapon &deathscythe, weapon &hellsplitter, monster &kulu, monster &bar, monster &dia, monster &dummy) {
	system("cls");
	char choice;
	
	do {
		
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
        cout << "\t\t\t\t\t\t[C]olosseum Store" << endl;
        cout << "\t\t\t\t\t\t[T]utorial" << endl;
        cout << "\t\t\t\t\t\t[E]nter Arena" << endl;
        cout << "\t\t\t\t\t\t[R]eturn to Login" << endl;
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
        	case 'C':
        	case 'c':
        		system("cls");
        		store(uinfo, buster, deathscythe, hellsplitter);
        		break;
        	case 'T':
        	case 't':
        		system("cls");
        		tutorial(uinfo, buster, deathscythe, hellsplitter, kulu, bar, dia, dummy);
        		break;
        	case 'E':
        	case 'e':
        		arena(uinfo, buster, deathscythe, hellsplitter, kulu, bar, dia);
        		break;
        	case 'R':
        	case 'r':
        		system("cls");
        		cout << "\t\t\t\t\t\tYou are now returning to login" << endl;
        		system("pause");
        		system("cls");
        		break;
        	default:
        		system("cls");
            	cout << "\t\t\t\t\t\tInvalid Input!!!";
            	break;
		}
        
	} while (choice != 'R' && choice != 'r');
	
}

void save(const userinfo &uinfo) {
    ofstream outFile("userdata.txt");

    if (outFile.is_open()) {
        outFile << uinfo.username << endl;
        outFile << uinfo.userzenny << endl;
        outFile << uinfo.equippedGS << endl;
        outFile << uinfo.equippedGSdmg << endl;
        outFile << uinfo.healthpots << endl;

        cout << "\n\n\t\t\t\t\tGame saved successfully!" << endl;
        outFile.close();
    } else {
        cout << "Error saving game data to userdata.txt" << endl;
    }
}
