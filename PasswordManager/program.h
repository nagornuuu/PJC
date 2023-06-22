#ifndef PASSWORDMANAGER_PROGRAM_H
#define PASSWORDMANAGER_PROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "password.h"

static std::regex rgx = std::regex("[^( \\s\\|\\s)]+");  // regex do sprawdzania, czy ciąg nie jest pusty
static std::string passwordsFileName = "file_passwords_enc.txt";     // nazwa pliku z ogolnem haslem

class PasswordManager{

public:

    void static start();
    void static openPasswordFile();
    void static openPasswordFileBySelf();
    void static openFile(std::string plikPath);
    void static append(std::string str, std::string plikPath);
    void static addPassword(std::string path);
    void static addCategory(std::string path);
    void static deletePassword(std::string path);
    void static deleteCategory(std::string path);
    void static editPassword(std::string path);
    std::string static getCurrentDateTime();
    static std::vector<std::string> getRegexMatches(std::string str);
    std::vector<std::string> static getCategoryList(std::string path);
    std::vector<Password> static getPasswordList(std::string path);
    std::vector<Password> static getFilteredPasswordList(std::vector<Password>& vec, std::vector<std::string> categ);
    std::vector<Password> static getSortedPasswordList(std::vector<Password>& vec);
    static std::string getPasswordsFileName();

};

#endif //PASSWORDMANAGER_PROGRAM_H
