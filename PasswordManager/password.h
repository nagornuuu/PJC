#ifndef PASSWORDMANAGER_PASSWORD_H
#define PASSWORDMANAGER_PASSWORD_H

#include <string>
#include <vector>

 /**
  * Klasa reprezentująca hasło
  */
struct Password{
protected :
    std::string name, login, password, link, category;

public:
    Password(std::string n, std::string l, std::string p, std::string li, std::string c);

    std::string getName();
    std::string getLogin();
    std::string getPassword();
    std::string getLink();
    std::string getCategory();

    static void showPasswords(std::vector<Password> vec);
    static bool passwordCompare(Password obj1, Password obj2);
    static bool nameCompare(Password obj1, Password obj2);
    friend std::ostream& operator<<(std::ostream& os, const  Password& has);
};
#endif //PASSWORDMANAGER_PASSWORD_H
