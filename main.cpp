#include <iostream>
#include "functions.h"
#include <stdio.h>
#include <windows.h>
using namespace std;


int main() {
    vector<string> user_data = get_data();

    if (isAuthificate(user_data[0], user_data[1])) {
        cout << "CODE: 200" << endl;

        if (isAdmin(user_data[0], user_data[1])) {
            screen_clear();
            print_table();
            
            while (true) {
                cout << "[1] Create user" << endl;
                cout << "[2] Delete user" << endl;
                cout << "[3] Edit user password" << endl;
                cout << "[4] See all registered users" << endl;
                cout << "[5] Exit" << endl;
                cout << "> Choose an option: ";
                
                int choice;
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1:
                        screen_clear();
                        cout << "> Create a new user:" << endl;
                        create_user();
                        break;

                    case 2: {
                        screen_clear();
                        vector<string> file_name = check_dir();
                        for (const auto& name : file_name){
                            cout << "[dir]: " << name << endl;
                        }

                        cout << "> Enter login of the user to delete: ";
                        string user_login;
                        cin >> user_login;
                        cin.ignore();
                        delete_user(user_login);
                        break;
                    }

                    case 3: {
                        screen_clear();
                        vector<string> file_name = check_dir();
                        for (const auto& name : file_name){
                            cout << "[dir]: " << name << endl;
                        }

                        cout << "> Enter login of the user to edit password: ";
                        string user_login;
                        cin >> user_login;
                        cin.ignore();
                        admin_password(user_login);
                        break;
                    }

                    case 4: {
                        screen_clear();
                        cout << "> Registered users:" << endl;
                        auto users = check_dir();
                        for (const auto& user : users) {
                            cout << "- " << user << endl;
                        }
                        break;
                    }

                    case 5:
                        cout << "> Exiting... Goodbye!" << endl;
                        return 0;

                    default:
                        cout << "> Invalid option. Please try again." << endl;
                }

                Sleep(1000);
                screen_clear();
                print_table();
            }
        } else {
            while (true) {
                screen_clear();
                cout << "Welcome, " << user_data[0] << "!" << endl;
                cout << "[1] Change password" << endl;
                cout << "[2] Exit" << endl;
                cout << "> Choose an option: ";

                int choice;
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1:
                        screen_clear();
                        cout << "> Change password for user: " << user_data[0] << endl;
                        edit_password(user_data[0]);
                        break;

                    case 2:
                        cout << "> Exiting... Goodbye!" << endl;
                        return 0;

                    default:
                        cout << "> Invalid option. Please try again." << endl;
                }

                Sleep(1000);
            }
        }

        return 0;
    } else {
        cout << endl << "CODE: 403 - Access Denied." << endl;
        return 0;
    }

    return 0;
}
