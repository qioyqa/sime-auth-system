#include <iostream>
#include "functions.h"
using namespace std;


int main(){
    vector<string> user_data = get_data();

    if (isRegistred(user_data[0])){
        vector<string> data = read_file(user_data[0]);

        if (isTrue(data, user_data[0], user_data[1])){
            cout << ">Welcome back: " << user_data[0] << endl;
        } else {
            cout << ">Wrong password!";
        }
        return 0;

    } else {
        auto file = create_file(user_data[0]);
        if (file.second){
            write_to_file(file.first, user_data[0], user_data[1]);
        }

        cout << ">Dear, " << user_data[0] << " thank you for registration!" << endl;
        return 0;
    }

    return 0;
}