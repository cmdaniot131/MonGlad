#include <iostream>
#include <string>
using namespace std;

bool loginUser();
char mainMenu();

int main() {
    char choice;
    if (loginUser()) {
        cout << "Success! You are now logged in" << endl;
        choice = mainMenu();
        
    } else {
    	cout <<"\t\t\t\t\t==========================================" << endl;
        cout << "\t\t\t\t\tUnsuccessful log in.Thank you for playing." << endl;
        cout << "\t\t\t\t\t==========================================" << endl;
    }
    
    return 0;
}

bool loginUser() {
	// Add fstream
	char CorL;
	int loginAttempt = 0;
    string username, nUsername;
    
	cout << "\t\t\t\t\t\t [C]reate New User\n";
    cout << "\t\t\t\t\t\t [L]ogin\n";
    cout << "\n\t\t\t\t\t\t Enter your choice: ";
	cin >> CorL;
	cin.ignore();
	
	switch (CorL) {
		case 'C':
		case 'c':
			cout << "\n\t\t\t\t\t\tCreate new username: ";
    		getline(cin, nUsername);
    		
    		while (loginAttempt < 5) {
	        cout << "\n\t\t\t\t\t\tEnter your new username again: ";
	        getline(cin, username);
	
	        if (nUsername == username) {
	            return true;
	        } else {
	            cout << "\n\t\t\t\t\tUnsuccessful log in. Please try again" << endl;
	            loginAttempt++;
	        }
	    }
	    cout << "\n\t\t\t\t\t Too many login attempts. Account locked.\n" << endl;
	    return false;
		break;
		
		case 'L':
		case 'l':
			cout << "\n\t\t\t\t\t\tAccount Login Section";
			
			while (loginAttempt < 5 ) {
				cout << "\n\t\t\t\t\t\tEnter your username: ";
				getline(cin, username);
				
				if (nUsername == username) {
					return true;
				} else {
					cout << "\n\t\t\t\t\tINVALID USERNAME. Please try again";
					loginAttempt++;
				}
				
			}
			cout << "\n\t\t\t\t\t Too many login attempts. Account locked.\n" << endl;
	    	return false;
			break;
		
		default:
            cout << "\n\t\t\t\t\tInvalid choice. Please choose 'C' or 'L'.\n";
            return false;
	}

}

char mainMenu() {
    char choice;
    do {
        system("cls");
        cout << "\t\t\t\t\t\tLogin Successful!!!\n";
        
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
        
        cout << "\n\t\t\t\t\t\t [C]reate user\n"; //Add another fstream here
        cout << "\t\t\t\t\t\t [L]oad user\n";
        cout << "\t\t\t\t\t\t [T]utorial\n";
        cout << "\t\t\t\t\t\t [S]tore\n";
        cout << "\t\t\t\t\t\t E[x]it\n\n";
    	cout << "\t\t\t\t\t\t [R]eturn to Login System";
        cout << "\n\t\t\t\t\t\t Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 'C':
            case 'c':
                
                break;
            	
        }
    } while (choice != 'X' && choice != 'x');

    return 0;
}

