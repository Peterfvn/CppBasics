#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define FILEPATH "login.txt"

bool login(const std::string& user, const std::string& pass);
void createAccount();
bool verifyUsername(const std:: string& user);

int main() {
    int flag;
    std::string user;
    std::string pass;
    std::cout << "Login [1]\nCreate an Account [2]\n";
    if(std::cin >> flag) {
        switch (flag) {
            case 2:
                createAccount();
                break;
            case 1:
                std::cout << "Enter your username: "; std::cin >> user;
                std::cout << "Enter your password: "; std:: cin >> pass;
                if(login(user, pass)) {
                    std:: cout << "Successfully logged in!\n";
                } else {
                    std:: cout << "Failed to validate credientials\n";
                }
                break;
            default:
                std::cout << "Please enter '1' or '2'\n";
                break;
        }
    } else {
        std::cout << "Please enter an integer.\n";
    }
    return 0;
}

bool login(const std::string& user, const std::string& pass) {
    std::ifstream loginFile(FILEPATH);
    if(loginFile.is_open()) {
        std::string line;
        std::string username;
        while(std::getline(loginFile, line)) {
            size_t space = line.find(' ');
            username = line.substr(0, space);
            if(username == user) {
                loginFile.close();
                std::string password = line.substr(space+1);
                if(password == pass) {
                    return true;
                }
                return false;
            }
        }
        loginFile.close();
        return false;
    } else {
        std::cout << "Error opening the file containing logins.\n";
        return false;
    }
}

bool verifyUsername(const std:: string& user) {
std::ifstream loginFile(FILEPATH);
    if(loginFile.is_open()) {
        std::string line;
        while(std::getline(loginFile, line)) {
            size_t space = line.find(' ');
            line = line.substr(0, space);
            if(line == user) {
                loginFile.close();
                return true;
            }
        }
        loginFile.close();
        return false;
    } else {
        std::cout << "Error opening the file containing logins.\n";
        return false;
    }
}

void createAccount(){
    std::string user;
    std::string pass;
    std::cout << "Create a username: "; std::cin >> user;
    std::cout << "Create a password: "; std::cin >> pass;
    //verify that this is a unique username
    if(verifyUsername(user)) {
        std::cout << "Username taken.\n";
        return;
    }
    std:: ofstream createUser(FILEPATH, std::ios::app);
    if(createUser.is_open()) {
        createUser << user << ' ' << pass << std::endl;
        createUser.close();
        std::cout << "User successfully added\n";
    } else {
        std:: cout << "Error adding user.\n";
    }
}