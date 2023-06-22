#include "password.h"
#include <string>
#include <iostream>
#include <vector>

Password::Password(std::string n, std::string l, std::string p, std::string li, std::string c) {
    name = n;
    login = l;
    password = p;
    link = li;
    category = c;
}
std::string Password::getName() {
    return name;
}

std::string Password::getLogin(){
    return login;
}

std::string Password::getPassword(){
    return password;
}

std::string Password::getLink(){
    return link;
}

std::string Password::getCategory() {
    return category;
}

void Password::showPasswords(std::vector<Password> vec) {
    if (vec.empty()) {
        std::cout << "------- Pusto --------" << std::endl;
        return;
    }
    std::cout << " " << std::endl;
    for (int i = 0; i < vec.size(); i++)
        std::cout << i + 1 << ") "<< vec[i] << std::endl;
    std::cout << " " << std::endl;
    return;
}

bool Password::passwordCompare(Password obj1, Password obj2) {
    return obj1.getPassword().length() > obj2.getPassword().length();
}
bool Password::nameCompare(Password obj1, Password obj2) {
    return obj1.getName() < obj2.getName();
}

std::ostream& operator<<(std::ostream& os, const Password& has){
    os << has.name << " | " << has.login << " | " << has.password << " | " << has.link << " | " << has.category;
    return os;
}