#include <iostream>
#include <cstdlib>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;
//this generates random seed based on current time at moment of execution
mt19937 generator(chrono::system_clock::now().time_since_epoch().count());

void clear_screen() {
    system("cls");
}

void print_banner() {
    cout << "\n";
    cout << "  ╔═══════════════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                                           ║\n";
    cout << "  ║  ██████╗  ██████╗ ███████╗███████╗ ██████╗██████╗ ██████╗ ██████╗██╗  ██╗\n";
    cout << "  ║  ██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║ ██╔╝\n";
    cout << "  ║  ██████╔╝███████║███████╗███████╗██║     ██████╔╝███████║██║     █████╔╝ \n";
    cout << "  ║  ██╔═══╝ ██╔══██║╚════██║╚════██║██║     ██╔══██╗██╔══██║██║     ██╔═██╗ \n";
    cout << "  ║  ██║     ██║  ██║███████║███████║╚██████╗██║  ██║██║  ██║╚██████╗██║  ██╗\n";
    cout << "  ║  ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n";
    cout << "  ║                                                                           ║\n";
    cout << "  ║                    Advanced Password Cracking Utility                    ║\n";
    cout << "  ║                         Version 1.0 | 2026 Edition                       ║\n";
    cout << "  ║                        [ For Educational Use Only ]                      ║\n";
    cout << "  ║                                                                           ║\n";
    cout << "  ╚═══════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void print_menu() {
    //add more options. potentially add option for users to just generate a password for personal use?
    cout << "  ┌───────────────────────────────────────────────────────────────────────────┐\n";
    cout << "  │                          SELECT AN ATTACK METHOD                          │\n";
    cout << "  ├───────────────────────────────────────────────────────────────────────────┤\n";
    cout << "  │                                                                           │\n";
    cout << "  │    [1] → Bruteforce 4-Digit Numeric Password                              │\n";
    cout << "  │    [2] → Bruteforce 6-Digit Numeric Password                              │\n";
    cout << "  │    [3] → Bruteforce 8-Digit Numeric Password                              │\n";
    cout << "  │    [4] → Dictionary Attack with Custom Wordlist                           │\n";
    cout << "  │    [5] → Exit PassCrack                                                   │\n";
    cout << "  │                                                                           │\n";
    cout << "  └───────────────────────────────────────────────────────────────────────────┘\n";
    cout << "\n  >> Enter your choice: ";
}

void print_separator() {
    cout << "  ═══════════════════════════════════════════════════════════════════════════\n";
}

void status_msg(const string& msg) {
    cout << " [*]" << msg << endl;
}

void success_msg(const string& msg) {
    cout << " [+] " << msg << endl;
}

void error_msg(const string& msg) {
    cout << " [!] " << msg << endl;
}

//todo: add function for just normal password generation. allow input 
//like name, dob, and petnames to generate personalized passwords. 

//function for generating four digit passwords
int four_digit_password() {

    cout << "Iterating thorugh possible four digit passwords..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    uniform_int_distribution<int> distribution(1000, 9999);

    while (true) {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit()) {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

//function for generating six digit passwords
int six_digit_password() {
    uniform_int_distribution<int> distribution(100000, 999999);

    cout << "Iterating through possible six digit password..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (true) {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit()) {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

//function for generating eight digit passwords
int eight_digit_password() {
    uniform_int_distribution<int> distribution(10000000, 99999999);

    cout << "Iterating through possible eight digit password..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (true) {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit()) {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

vector<string> generate_possible_passwords(string word) {
    vector <string> passwords;

    passwords.push_back(word);

    string lower = word;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    passwords.push_back(lower);

    string upper = word;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    passwords.push_back(upper);

    string capitalized = lower;
    if(!capitalized.empty()) {
        capitalized[0] = toupper(capitalized[0]);
    }
    passwords.push_back(capitalized);

    string leet = lower;
    //leetspeak substitutions
    for (char& c : leet) {
        if (c == 'a') c = '4';
        else if (c == 'e') c = '3';
        else if (c == 'i') c = '1';
        else if (c == 'o') c = '0';
        else if (c == 's') c = '5';
        else if (c == 't') c = '7';
    }
    passwords.push_back(leet);

    passwords.push_back(lower + "123");
    passwords.push_back(lower + "!");
    passwords.push_back(capitalized + "123");
    return passwords;
    //todo: create feature to concatenate all words in the wordlist together
}

void alphabetical_password_guesser(vector<string> wordlist) {
    cout << "Attempting alphabetical password guessing..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (const string& word : wordlist) {
        vector<string> passwords = generate_possible_passwords(word);
        for (const string& variant : passwords) {
            cout << "Trying: " << variant << endl;

            if(_kbhit()) {
                _getch();
                cout << "--------------------------------------------------------------" << endl;
                cout << "Password guessing stopped by user." << endl;
                return;
            }
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "completed all variations." << endl;
}

int main() {
    clear_screen();
    print_banner();
    print_menu();

    int choice;
    cin >> choice;

    clear_screen();
    print_banner();
    print_separator();
    switch (choice) {
        //Choice structure for selecting bruteforce methods
        case 1:
            status_msg("Initializing 4-digit bruteforce...");
            print_separator();
            four_digit_password();
            break;
        case 2:
            status_msg("Initializing 6-digit bruteforce...");
            print_separator();
            six_digit_password();
            break;
        case 3:
            status_msg("Initializing 8-digit bruteforce...");
            print_separator();
            eight_digit_password();
            break;
            //todo: add ability to send input to a device such as a phone over USB port. 
            //would require additional libraries and permissions, but would be a powerful 
            //feature for testing the strength of your own devices.
        case 4: {
            vector <string> wordlist;
            status_msg("Dictionary attack selected.");
            print_separator();
            cout << "Enter words for the wordlist (type 'done' to finish):" << endl;
            string word;
            while (cin >> word && word != "done") {
                wordlist.push_back(word);
                success_msg("added: " + word);
            }
            print_separator();
            alphabetical_password_guesser(wordlist);
            break;
        }
        
        case 5:
            status_msg("Exiting PassCrack");
            print_separator();
            break;
        default:
            cout << "You must pick something." << endl;
    }

    cout << "\n Press any key to exit..." << endl;
    _getch();
    return 0;
}
