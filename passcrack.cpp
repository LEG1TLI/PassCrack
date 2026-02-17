#include <iostream>
#include <cstdlib>
#include <chrono>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
#include <fstream>
#include <unordered_set>
#include <cctype>
using namespace std;
using namespace chrono;
// this generates random seed based on current time at moment of execution
mt19937 generator(system_clock::now().time_since_epoch().count());

void clear_screen()
{
    system("cls");
}

void print_banner()
{
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
    cout << "  ║                    Advanced Password Cracking Utility                     ║\n";
    cout << "  ║                         Version 1.0.1 | 2026 Edition                      ║\n";
    cout << "  ║                        [ For Educational Use Only ]                       ║\n";
    cout << "  ║                                                                           ║\n";
    cout << "  ╚═══════════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void print_menu()
{
    // add more options. potentially add option for users to just generate a password for personal use?
    cout << "  ┌───────────────────────────────────────────────────────────────────────────┐\n";
    cout << "  │                          SELECT AN ATTACK METHOD                          │\n";
    cout << "  ├───────────────────────────────────────────────────────────────────────────┤\n";
    cout << "  │                                                                           │\n";
    cout << "  │    [1] → Bruteforce 4-Digit Numeric Password                              │\n";
    cout << "  │    [2] → Bruteforce 6-Digit Numeric Password                              │\n";
    cout << "  │    [3] → Bruteforce 8-Digit Numeric Password                              │\n";
    cout << "  │    [4] → Dictionary Attack with Custom Wordlist                           │\n";
    cout << "  │    [5] → Generate personalized password                                   │\n";
    cout << "  │    [6] → Exit PassCrack                                                   │\n";
    cout << "  └───────────────────────────────────────────────────────────────────────────┘\n";
    cout << "\n  >> Enter your choice: ";
}

static inline string to_upr_cpy(const string &s)
{
    string out(s);
    transform(out.begin(), out.end(), out.begin(),
              [](unsigned char c)
              {
                  return static_cast<char>(toupper(c));
              });
    return out;
}

static inline string to_lwr_cpy(const string &s)
{
    string out(s);
    transform(out.begin(), out.end(), out.begin(),
              [](unsigned char c)
              {
                  return static_cast<char>(tolower(c));
              });
    return out;
}

void print_separator()
{
    cout << "  ═══════════════════════════════════════════════════════════════════════════\n";
}

void status_msg(const string &msg)
{
    cout << " [*]" << msg << endl;
}

void success_msg(const string &msg)
{
    cout << " [+] " << msg << endl;
}

void error_msg(const string &msg)
{
    cout << " [!] " << msg << endl;
}

// todo: add function for just normal password generation. allow input
// like name, dob, and petnames to generate personalized passwords.

// function for generating four digit passwords
int four_digit_password()
{

    cout << "Iterating thorugh possible four digit passwords..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    uniform_int_distribution<int> distribution(1000, 9999);

    while (true)
    {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit())
        {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

// function for generating six digit passwords
int six_digit_password()
{
    uniform_int_distribution<int> distribution(100000, 999999);

    cout << "Iterating through possible six digit password..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (true)
    {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit())
        {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

// function for generating eight digit passwords
int eight_digit_password()
{
    uniform_int_distribution<int> distribution(10000000, 99999999);

    cout << "Iterating through possible eight digit password..." << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (true)
    {
        int password = distribution(generator);
        cout << password << endl;

        if (_kbhit())
        {
            _getch();
            break;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "generation stopped by user." << endl;
    return 0;
}

vector<string> generate_possible_passwords(const string &word)
{
    unordered_set<string> seen;
    auto add = [&](string s)
    {
        if (!s.empty())
            seen.insert(move(s));
    };
    add(word);
    string lower = to_lwr_cpy(word);
    add(lower);
    add(to_upr_cpy(word));

    if (!lower.empty())
    {
        string cap = lower;
        cap[0] = static_cast<char>(toupper(static_cast<unsigned char>(cap[0])));
        add(cap);
    }

    string leet = lower;
    for (char &c : leet)
    {
        switch (static_cast<unsigned char>(c))
        {
        case 'a':
            c = '4';
            break;
        case 'e':
            c = '3';
            break;
        case 'i':
            c = '1';
            break;
        case 'o':
            c = '0';
            break;
        case 's':
            c = '5';
            break;
        case 't':
            c = '7';
            break;
        default:
            break;
        }
    }
    add(leet);

    add(lower + "123");
    add(lower + "!");
    if (!lower.empty())
        add(string(1, static_cast<char>(toupper(static_cast<unsigned char>(lower[0])))) + lower.substr(1) + "123");
    
    vector<string> out;
    out.reserve(seen.size());
    for (auto& s : seen) out.push_back(s);
    return out;
}





bool alphabetical_password_guesser(vector<string>& wordlist)
{
    string target_password;
    cout << "Enter target password: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    print_separator();
    cout << "Starting dictionary attack..." << endl;

    //input sanitization
    vector<string> clean;
    clean.reserve(wordlist.size());
    for (auto& w : wordlist) 
    {
        string t = w;
        auto l = t.find_first_not_of(" \t\r\n");
        if (l == string::npos) continue;
        auto r = t.find_last_not_of(" \t\r\n");
        clean.push_back(t.substr(1, r - l + 1));
    }

    int attempts = 0;
    auto start_time = steady_clock::now();
    //reduce console clutter
    const int print_every = 1000;

    for(const string& word : clean) 
    {
        auto variations = generate_possible_passwords(word);
        for (const string& variation : variations) 
        {
            ++attempts;
            if((attempts % print_every) == 0)
            {
                cout << "[" << attempts << "] Trying: " << variation << endl;
            }

            if(variation == target_password) 
            {
                auto end_time = steady_clock::now();
                double secs = duration_cast<duration<double>>(end_time - start_time).count();
                success_msg("Password found: " + variation);
                print_separator();
                success_msg("Base word: " + word);
                success_msg("Total attempts: " + to_string(attempts));
                success_msg("Time taken: " + to_string(secs) + " seconds");
                print_separator();
                return true;
            }
        }
    }

    error_msg("Password not found in wordlist");
    return false;

}

void wordlist_frm_file(vector<string> &wordlist)
{
    string filepath;
    cout << "Enter path to wordlist: " << endl;
    cin.ignore();
    getline(cin, filepath);

    ifstream file(filepath);

    if (!file.is_open())
    {
        error_msg("Failed to open file at: " + filepath);
        return;
    }

    string word;
    int count = 0;
    while (getline(file, word))
    {
        word.erase(word.find_last_not_of(" \n\r\t") + 1);
        if (!word.empty())
        {
            wordlist.push_back(word);
            count++;
        }
    }

    file.close();
    success_msg("Loaded " + to_string(count) + " words from file.");
    print_separator();
}

void generate_personal_pwd()
{
    cout << "Personalized password generation coming soon!" << endl;
    cout << "this feature is meant for generating a password, either for your own pentesting purposes or just to use on a day to day basis!" << endl;
}

int main()
{
    clear_screen();
    print_banner();
    print_menu();

    int choice;
    cin >> choice;

    clear_screen();
    print_banner();
    print_separator();
    switch (choice)
    {
    // Choice structure for selecting bruteforce methods
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
        // todo: add ability to send input to a device such as a phone over USB port.
        // would require additional libraries and permissions, but would be a powerful
        // feature for testing the strength of your own devices.
    case 4:
    {
        vector<string> wordlist;
        status_msg("Dictionary attack selected. ");
        print_separator();

        cout << " [1] >> load wordlist from file (enter filepath)" << endl;
        cout << " [2] >> enter custom words (comma separated)" << endl;
        cout << " >> choose option: ";

        int option;
        cin >> option;
        print_separator();

        if (option == 1)
        {
            wordlist_frm_file(wordlist);
        }
        else
        {
            cout << " Enter custom words (comma separated, type 'done' to finish): \n\n"
                 << endl;
            string word;
            cin.ignore();
            while (getline(cin, word) && word != "done")
            {
                if (!word.empty())
                {
                    wordlist.push_back(word);
                    success_msg("Added word: " + word);
                }
            }
            print_separator();
        }
        if (!wordlist.empty())
        {
            alphabetical_password_guesser(wordlist);
        }
        else
        {
            error_msg("No words provided for dictionary attack.");
        }
        break;
    }

    case 5:
        status_msg("Personalized password generation selected.");
        print_separator();
        break;
    case 6:
        status_msg("Exiting PassCrack. Goodbye!");
        print_separator();
        break;
    default:
        cout << "You must pick something." << endl;
    }

    cout << "\n Press any key to exit..." << endl;
    _getch();
    return 0;
}
