#include <fstream>
#include <vector>
#include <filesystem>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
namespace fs = std::filesystem;
using namespace std;
using namespace fs;

pair<string, bool> create_file(const string& file_name = "admin"){
    string ffile_name = file_name + ".txt";
    ofstream file(ffile_name);
    if (file.is_open()){
        file.close();
        return {file_name, true};
    } else {
        return {file_name, false};
    }
}

void write_to_file(const string& file_name = "admin", string login = "admin", string password = "admin"){
    string ffile_name = file_name + ".txt";
    ofstream file(ffile_name);    
    file << login << endl;
    file << password;
    file.close();
}

vector<string> read_file(const string& file_name = "admin"){
    string ffile_name = file_name + ".txt";
    ifstream file(ffile_name);
    string p_temp{""};
    vector<string> data;

    while (getline (file, p_temp)){
        data.push_back(p_temp);
    }


    file.close();
    return data;
}

vector<string> check_dir(){
    string path{"."};
    vector<string> file_names;

    if(exists(path) && is_directory(path)){

        for (const auto& entry : directory_iterator(path)){
            if (is_regular_file(entry)){
                file_names.push_back(entry.path().filename().string());
            }
        }
    }
    return file_names;
}

bool isRegistred(const string& login = "admin"){
    auto file_names = check_dir();
    string validate_login = login + ".txt";
    for(const auto& name : file_names){
        if ((validate_login) == name){
            return true;
        }
    }

    return false;
}

string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}


string get_password() {
    string password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*"; 
        }
    }
    cout << endl;
    return password;
}

vector<string> get_data(){
    vector<string> data;
    string login{"admin"}, passwd{"admin"}; 

    
    cout << ">login: ";
    cin >> login;
    cin.ignore();
    cout << endl;
    cout << ">password: ";
    passwd = get_password();
    cout << endl;

    data.push_back(login);
    data.push_back(passwd);

    return data;
}

bool isTrue(vector<string> data, const string& login = "admin", const string& passwd = "admin") {
    if(trim(login) == trim(data[0]) && trim(passwd) == trim(data[1])) {
        return true;
    } else {
        return false;
    }
}

bool isAuthificate(const string& login, const string& password) {
    if (isRegistred(login)) {
        vector<string> data = read_file(login);

        if (isTrue(data, login, password)) {
            cout << "> Welcome back, " << login << "!" << endl;
            return true;
        } else {
            cout << "> Wrong password!" << endl;
            return false;
        }
    } else {
        auto file = create_file(login);
        if (file.second) {
            write_to_file(file.first, login, password);
            cout << "> Dear " << login << ", thank you for registering!" << endl;
            return true;
        } else {
            cerr << "> Error: Unable to create a file for the user." << endl;
            return false;
        }
    }
}

bool isAdmin(const string& login, const string& password){
    if (read_file(login)[0] == "admin" && password == "admin"){
        cout << ">logined as admin " << endl;
        return true;
    } else {
        return false;
    }
}

void delete_user(const string& login){
    if(isRegistred(login)){
        string ffile = login + ".txt";
        if (remove(ffile.c_str()) == 0){
            cout << "User: " << login << " deleted successfully" << endl;
        } else {
            cout << "Can't delete this user!" << endl;
        }
    } else {
        cout << "User not registered!" << endl;
    }
}

void create_user(){
    vector<string> user_data = get_data();
    auto file = create_file(user_data[0]);
    if (file.second){
        write_to_file(user_data[0], user_data[0], user_data[1]);
        cout << "User: " << user_data[0] << "created succesfully" << endl;
    } else {
        cout << "Can`t open file, try again." << endl;
    }
}

void screen_clear(){
    Sleep(100);
    system("cls");
}

void print_table() {
    cout << R"(
            .___      .__                                    .__   
_____     __| _/_____ |__| ____   ___________    ____   ____ |  |  
\__  \   / __ |/     \|  |/    \  \____ \__  \  /    \_/ __ \|  |  
 / __ \_/ /_/ |  Y Y  \  |   |  \ |  |_> > __ \|   |  \  ___/|  |__
(____  /\____ |__|_|  /__|___|  / |   __(____  /___|  /\___  >____/
     \/      \/     \/        \/  |__|       \/     \/     \/      
    )" << endl;
}

void edit_password(const string& login) {
    if (isRegistred(login)) {
        vector<string> user_data = read_file(login);

        cout << "> Current password required for " << login << ":" << endl;
        string current_password = get_password();

        if (isTrue(user_data, login, current_password)) {
            cout << "> Enter new password: ";
            string new_password = get_password();
            cout << "> Confirm new password: ";
            string confirm_password = get_password();

            if (new_password == confirm_password) {
                write_to_file(login, login, new_password);
                cout << "> Password updated successfully for user: " << login << endl;
            } else {
                cout << "> Error: Passwords do not match. Try again." << endl;
            }
        } else {
            cout << "> Error: Incorrect current password." << endl;
        }
    } else {
        cout << "> Error: User " << login << " is not registered." << endl;
    }
}

void admin_password(const string& login){
    cout << "> Enter new password for user \"" << login << "\":" << endl;
    string new_password = get_password();
    cout << "> Confirm new password for user \"" << login << "\":" << endl;
    string confirm_password = get_password();

    if (new_password == confirm_password) {
        write_to_file(login, login, new_password);
        cout << "> Password updated successfully for user: " << login << endl;
    } else {
        cout << "> Error: Passwords do not match. Try again." << endl;
    }
}


