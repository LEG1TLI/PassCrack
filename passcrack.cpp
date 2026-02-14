#include <iostream>
#include <cstdlib>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

mt19937 generator(chrono::system_clock::now().time_since_epoch().count());

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
    cout << "Welcome to PassCrack!" << endl;
    cout << "Please select an option:" << endl;
    cout << "1. Bruteforce four digit password" << endl;
    cout << "2. Bruteforce six digit password" << endl;
    cout << "3. Bruteforce eight digit password" << endl;
    cout << "4. Alphabetical password guessing with wordlist" << endl;
    cout << "5. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            four_digit_password();
            break;
        case 2:
            six_digit_password();
            break;
        case 3:
            eight_digit_password();
            break;
        case 4: {
            vector <string> wordlist;
            cout << "Enter words for the wordlist (type 'done' to finish):" << endl;
            string word;
            while (cin >> word && word != "done") {
                wordlist.push_back(word);
            }
            alphabetical_password_guesser(wordlist);
            break;
        }
        
        case 5:
            cout << "Exiting Passcrack." << endl;
            break;
        default:
            cout << "You must pick something." << endl;
    }
    return 0;
}
