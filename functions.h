#include <fstream>
#include <vector>
#include <filesystem>
#include <conio.h>
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
