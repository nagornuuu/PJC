#include "program.h"
#include <iostream>
#include <string>
#include <regex>
#include "coder.h"
#include "password.h"
/**
 * metoda start() zwraca wynik dzialania programu
 */
void PasswordManager::start() {
    std::cout << "Wybierz wariant jak chcesz otworzyc plik:" << std::endl;
    std::cout << "a) Otworzyc plik z haslami" << std::endl;
    std::cout << "b) Wpisac sciezke samemu" << std::endl;

    char option{};
    std::cin >> option;

    switch(option) {
        case 'a' :
            openPasswordFile();
            break;
        case 'b' :
            openPasswordFileBySelf();
            break;
        default:
            std::cout << "Niema takiego wariantu! Sproboj ponownie" << std::endl;
            start();
    }
}

/**
 * metoda openPasswordFile() otwiera plik z haslami jaki znajduje sie w katalogu
 * z ktorego wykonywany jest program.
 */
void PasswordManager::openPasswordFile() {
    int option;
    std::vector<std::string> files {" haslo.txt",
                                    " haslo1.txt",
                                    " haslo2.txt"
    };

    std::cout << "Wybierz plik do otwarcia:"  << std::endl;
    for (int i = 0; i < files.size(); i++) {                       // wypisuje liste plikow
        std::cout << i + 1 << ") " << files[i] << std::endl;
    }
    std::string passwordPlik;
    auto path = std::string();
    auto file = std::fstream(path);
    auto str = std::string();
    std::cin >> option;

    if (option == 1) {
        std::cout << "Wprowadz haslo ogolne do wprowadzonego pliku: " << std::endl;
        std::cin >> passwordPlik;
        std::ifstream passwordFileReader(getPasswordsFileName());
        std::string line;
        std::vector<std::string> mainPassword;
        bool dostep = false;
        while (passwordFileReader.eof() == false) {                                      // sprawdza czy haslo jest poprawne
            getline(passwordFileReader, line);                                    // pobiera linie z pliku

            mainPassword = getRegexMatches(coder::decrypt(line));                // pobiera haslo z linii

            if (mainPassword.size() == 3 && mainPassword[1] == passwordPlik) {           // jesli haslo jest poprawne
                std::cout << "Haslo zostalo wprowadzone poprawnie.\n" << std::endl;       // wyswietla komunikat
                dostep = true;
                break;
            } else if (mainPassword.size() == 3 &&  mainPassword[1] != passwordPlik) {   // jesli haslo jest niepoprawne
                std::cout << "Zle haslo.\n" << std::endl;                                // wyswietla komunikat
                return;
            }
        }
        path = std::string ("C:\\Users\\andrii\\PasswordManager\\haslo.txt");         // ustawia sciezke do pliku
        while (file >> str) {                                                            // wczytuje plik
            std::cout << str << ' ';
        }
        openFile(path);                                                           // otwiera plik
    } else if (option == 2) {
        std::cout << "Wprowadz haslo ogolne do wprowadzonego pliku: " << std::endl;
        std::cin >> passwordPlik;
        std::ifstream passwordFileReader(getPasswordsFileName());
        std::string line;
        std::vector<std::string> mainPassword;
        bool dostep = false;
        while (passwordFileReader.eof() == false) {
            getline(passwordFileReader, line);

            mainPassword = getRegexMatches(coder::decrypt(line));

            if (mainPassword.size() == 3 && mainPassword[1] == passwordPlik) {
                std::cout << "Haslo zostalo wprowadzone poprawnie.\n" << std::endl;
                dostep = true;
                break;
            } else if (mainPassword.size() == 3 &&  mainPassword[1] != passwordPlik) {
                std::cout << "Zle haslo.\n" << std::endl;
                return;
            }
        }
        path = std::string ("C:\\Users\\andrii\\PasswordManager\\haslo1.txt");
        while (file >> str) {
            std::cout << str << ' ';
        }
        openFile(path);
    } else if (option == 3) {
        std::cout << "Wprowadz haslo ogolne do wprowadzonego pliku: " << std::endl;
        std::cin >> passwordPlik;
        std::ifstream passwordFileReader(getPasswordsFileName());
        std::string line;
        std::vector<std::string> mainPassword;
        bool dostep = false;
        while (passwordFileReader.eof() == false) {
            getline(passwordFileReader, line);

            mainPassword = getRegexMatches(coder::decrypt(line));

            if (mainPassword.size() == 3 && mainPassword[1] == passwordPlik) {
                std::cout << "Haslo zostalo wprowadzone poprawnie.\n" << std::endl;
                dostep = true;
                break;
            } else if (mainPassword.size() == 3 &&  mainPassword[1] != passwordPlik) {
                std::cout << "Zle haslo.\n" << std::endl;
                return;
            }
        }
        path = std::string ("C:\\Users\\andrii\\PasswordManager\\haslo2.txt");
        while (file >> str) {
            std::cout << str << ' ';
        }
        openFile(path);
    }
}

/**
 * metoda openPasswordFileBySelf() otwiera plik z haslami jaki znajduje sie w katalogu
 * wyproszony przez uzytkownika.
 */
void PasswordManager::openPasswordFileBySelf() {
    std::string pathPlik, passwordPlik;

    std::cout << "Wprowadz sciezke do pliku:" << std::endl;
    std::cin >> pathPlik;

    std::cout << "Wprowadz haslo ogolne do wprowadzonego pliku: " << std::endl;
    std::cin >> passwordPlik;

    std::ifstream passwordFileReader(getPasswordsFileName());
    std::string line;
    std::vector<std::string> mainPassword;

    bool dostep = false;

    while (passwordFileReader.eof() == false) {
        getline(passwordFileReader, line);

        mainPassword = getRegexMatches(coder::decrypt(line));

        if (mainPassword.size() == 3 && mainPassword[0] == pathPlik && mainPassword[1] == passwordPlik) {
            std::cout << "Haslo zostalo wprowadzone poprawnie.\n" << std::endl;
            dostep = true;
            break;
        } else if (mainPassword.size() == 3 && mainPassword[0] == pathPlik && mainPassword[1] != passwordPlik) {
            std::cout << "Zle haslo.\n" << std::endl;
            return;
        }
    }

    passwordFileReader.close();

    if (dostep == false) {
        std::cout << "Nie znaleziono pliku w podanej sciezce." << std::endl;
        return;
    }

    std::cout << "\tDostep przyznany, data autoryzacjy - " << mainPassword[2] << std::endl; // wyswietla data autoryzacji

    getCurrentDateTime();                                                          // aktualizuje date autoryzacji
    openFile(pathPlik);
}

/**
 * metoda openFile() otwiera plik.
 * path - sciezka do pliku
 */
void PasswordManager::openFile(std::string plikPath) {
    while(true) {

        std::vector<Password> passwords = getPasswordList(plikPath);                // pobiera liste hasel z pliku
        std::vector<std::string> categories = getCategoryList(plikPath);            // pobiera liste kategorii z pliku

        char settings{};
        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1) Wyszukaj hasla" << std::endl;
        std::cout << "2) Posortuj hasla" << std::endl;
        std::cout << "3) Dodaj haslo" << std::endl;
        std::cout << "4) Edytuj haslo" << std::endl;
        std::cout << "5) Usun haslo" << std::endl;
        std::cout << "6) Dodaj kategorie" << std::endl;
        std::cout << "7) Usun kategorie" << std::endl;
        std::cout << "8) Zakonczyc program" << std::endl;

        std::cin >> settings;
        switch (settings) {
            case '1' :
                Password::showPasswords(getFilteredPasswordList(passwords, categories));
                break;
            case '2' :
                Password::showPasswords(getSortedPasswordList(passwords));
                break;
            case '3' :
                addPassword(plikPath);
                break;
            case '4' :
                editPassword(plikPath);
                break;
            case '5' :
                deletePassword(plikPath);
                break;
            case '6' :
                addCategory(plikPath);
                break;
            case '7' :
                deleteCategory(plikPath);
                break;
            case '8' :
                return;
            default:
                std::cout << "Niema takiej opcji." << std::endl;
        }
    }
}

/**
 * metoda editPassword() edytuje haslo i zapisuje zmiany do pliku.
 */
void PasswordManager::editPassword(std::string path) {
    std::vector<Password> passwords = getPasswordList(path);
    std::vector<std::string> categories = getCategoryList(path);
    std::string newPassword;
    std::string newName;
    std::string newLogin;
    std::string newLink;
    std::string newCategory;
    int option;

    std::cout << "Wybierz haslo do edycji:" << std::endl;
    Password::showPasswords(passwords);
    std::cin >> option;
    passwords.erase(passwords.begin() + option);

    if (passwords.size() == 0) {
        std::cout << "Brak hasel do edycji" << std::endl;
        return;
    }

    std::cout << "Zmien haslo" << std::endl;
    if (option = '1') {
        std::cout << "Wprowadz nowe nazwe:" << std::endl;
        std::cin >> newName;
        std::cout << "Wprowadz nowy login:" << std::endl;
        std::cin >> newLogin;
        std::cout << "Wprowadz nowe haslo:" << std::endl;
        std::cin >> newPassword;
        std::cout << "Wprowadz nowy link:" << std::endl;
        std::cin >> newLink;
        std::cout << "Wprowadz nowe kategorje:" << std::endl;
        std::cin >> newCategory;
        passwords.push_back(Password(newName, newLogin, newPassword, newLink, newCategory));
    }
    std::string finalText;
    for(Password pas : passwords)
        finalText += coder::encrypt(pas.getName() + " | " + pas.getLogin() + " | " + pas.getPassword() + " | " + pas.getLink() + " | " + pas.getCategory()) + "\n";

    std::ofstream update(path);
    update << finalText;
    update.close();

    std::cout << "Haslo zostalo zmienione." << std::endl;
}

/**
 * metoda getRegexMatches() zwraca wynik wykonania wyrazenia regularnego.
 */
std::vector<std::string> PasswordManager::getRegexMatches(std::string str) {
    std::vector<std::string> searched;
    for (auto it = std::sregex_iterator(str.begin(), str.end(), rgx); it != std::sregex_iterator(); ++it) { // wyszukuje wyrazenie regularne
        searched.push_back(it -> str());                                                                              // zapisuje wynik wyszukiwania
    }
    return searched;
}

/**
 * metoda append() dodaje glowne haslo do pliku
 */
void PasswordManager::append(std::string str, std::string plikPath) {
    std::ofstream plikOut;                                                             // otwiera plik do zapisu
    plikOut.open(plikPath, std::ios::app);
    plikOut << str << std::endl;                                                       // dodaje haslo do pliku
    plikOut.close();

}

/**
 * metoda getCurrentDateTime() zwraca aktualna date i czas
 */
std::string PasswordManager::getCurrentDateTime() {
    const time_t tm = time(nullptr);                                                                       // pobiera aktualna date i czas
    char buf[64];                                                                                               // zmienna do zapisu date i czasu
    strftime(buf, std::size(buf), "%d.%m.%Y-%X", localtime(&tm));                 // zapisuje date i czas do zmiennej
    return buf;                                                                                                 // zwraca date i czas
}

/**
 * metoda getFilteredPasswordList() zwraca liste hasel z pliku po filtracji
 * passwords - lista hasel
 * categories - lista kategorii
 */
std::vector<Password> PasswordManager::getFilteredPasswordList(std::vector<Password>& vec, std::vector<std::string> categ) {
    std::cout << "Wybierz kategorie:" << std::endl;
    std::cout << "/////////////////////" << std::endl;
    for(int i = 0; i < categ.size();i++) {
        std::cout << i + 1 << ". " << categ[i] << std::endl;                              // wyswietla liste kategorii
    }
    std::cout << "/////////////////////" << std::endl;

    std::vector<Password> result;
    int option;
    std::cin >> option;
    for (int i = 0; i < vec.size(); i++) {                                                // przeglada liste hasel
        if (vec[i].getCategory() != categ[option - 1]) {                                  // jesli kategoria nie zgadza sie z wybrana
            vec.erase(vec.begin() + i);                                           // usuwa haslo
        }
    }
    return vec;
}

/**
 * metoda getSortedPasswordList() zwraca liste hasel z pliku po sortowaniu
 */
std::vector<Password> PasswordManager::getSortedPasswordList(std::vector<Password>& vec) {
    std::cout << "Wybierz sortowanie jakie chcesz:" << std::endl;
    std::cout << "1) Sortowanie hasel alfabetycznie;" << std::endl;
    std::cout << "2) Sortowanie hasel wedlug dlugosci;" << std::endl;

    int option;
    std::cin >> option;

    switch (option) {
        case 1:
            sort(vec.begin(), vec.end(), Password::nameCompare);     // sortuje liste hasel po nazwie
            break;
        case 2:
            sort(vec.begin(), vec.end(), Password::passwordCompare); // sortuje liste hasel po dlugosci
            break;
        default:
            std::cout << "Niema takiej opcji." << std::endl;
    }
    return vec;
}

/**
 * metoda addPassword() dodaje haslo do pliku
 */
void PasswordManager::addPassword(std::string path) {
    std::string name, login, password, category, link;
    std::vector<std::string> usedCateg = getCategoryList(path);                 // pobiera liste kategorii z pliku

    std::cout << "Wpisz nazwe dla hasla:" << std::endl;
    std::cin >> name;
    std::cout << "Wpisz login (opcjonalnie, zeby uniknac, wpisz '-'):" << std::endl;
    std::cin >> login;
    std::cout << "Wpisz haslo:" << std::endl;
    std::cin >> password;
    std::cout << "Wpisz link (opcjonalnie, zeby uniknac, wpisz '-'):" << std::endl;
    std::cin >> link;

    if (usedCateg.empty()) {                                                   // jesli lista kategorii jest pusta
        std::cout << "Wpisz nowa kategorie:" << std::endl;
        std::cin >> category;
    } else {
        std::cout << "Wybierz kategorie (0 aby dodac nowa): \n" << std::endl;
        for (int i = 0; i < usedCateg.size(); i++) {
            std::cout << i + 1 << ". " << usedCateg[i] << std::endl;           // wyswietla liste kategorii
        }
        std::cout << std::endl;
        int option;
        std::cin >> option;

        if (option == 0) {
            std::cout << "Wpisz nowa kategorie:" << std::endl;
            std::cin >> category;
        } else if (option <= usedCateg.size()) {                     // jesli wybrana kategoria nie istnieje
            category = usedCateg[option - 1];                        // zapisuje kategorie
        } else {
            std::cout << "Nieznana kategoria." << std::endl;
            return;
        }
    }

    append(coder::encrypt(name + " | " + login + " | " + password + " | " + link + " | " + category), path);

    std::cout << "Haslo zostalo wpisane." << std::endl;
    return;

}

/**
 * metoda addCategory() dodaje kategorie do pliku
 */
void PasswordManager::addCategory(std::string path) {
    std::string name, login, password, link, category;
    std::vector<std::string> usedCateg = getCategoryList(path);
    std::cout << "Wpisz nazwe dla hasla:" << std::endl;
    std::cin >> name;
    std::cout << "Wpisz login (opcjonalnie, zeby uniknac, wpisz '-'):" << std::endl;
    std::cin >> login;
    std::cout << "Wpisz haslo:" << std::endl;
    std::cin >> password;
    std::cout << "Wpisz link (opcjonalnie, zeby uniknac, wpisz '-'):" << std::endl;
    std::cin >> link;
    if (usedCateg.empty()) {
        std::cout << "Wpisz nowa kategorie:" << std::endl;
        std::cin >> category;
    } else {
        std::cout << "Wybierz kategorie (0 aby dodac nowa): \n" << std::endl;
        for (int i = 0; i < usedCateg.size(); i++) {
            std::cout << i + 1 << ". " << usedCateg[i] << std::endl;
        }
        std::cout << std::endl;
        int option;
        std::cin >> option;

        if (option == 0) {
            std::cout << "Wpisz nowa kategorie:" << std::endl;
            std::cin >> category;
        } else if (option <= usedCateg.size()) {
            category = usedCateg[option - 1];
        } else {
            std::cout << "Nieznana kategoria." << std::endl;
            return;
        }
    }

    append(coder::encrypt(name + " | " + login + " | " + password + " | " + link + " | " + category), path);
    std::cout << "kategorja zostala wpisana." << std::endl;
    }

/**
 * metoda deletePassword() usuwa haslo z pliku
 */
void PasswordManager::deletePassword(std::string path) {
    std::vector<Password> passwords = getPasswordList(path);                // pobiera liste hasel z pliku
    int option;

    std::cout << "Wpisz haslo do usuniecia: " << std::endl;
    Password::showPasswords(passwords);                                // wyswietla liste hasel

    std::cin >> option;

    passwords.erase(passwords.begin() + option - 1);                // usuwa haslo z listy

    std::string finalText;
    for(Password pas : passwords)
        finalText += coder::encrypt(pas.getName() + " | " + pas.getLogin() + " | " + pas.getPassword() + " | " + pas.getLink() + " | " + pas.getCategory()) + "\n";

    std::ofstream update(path);
    update << finalText;
    update.close();

    std::cout << "Haslo zostalo usuniete." << std::endl;
    return;
}

/**
 * metoda getCategoryList() pobiera liste kategorii z pliku
 */
std::vector<std::string> PasswordManager::getCategoryList(std::string path) {
    std::vector<std::string> category;                                       // lista kategorii
    std::string line;                                                        // linia z pliku
    std::vector<std::string> temp;                                           // lista z linii z pliku

    std::ifstream fileReader(path);

    if (fileReader.is_open() == false) {                                     // jesli plik nie istnieje
        return category;                                                     // zwraca pusta liste
    }

    while (fileReader.eof() == false) {                                      // dopoki nie dojdzie do konca pliku
        getline(fileReader, line);                                    // pobiera linie z pliku
        temp = getRegexMatches(coder::decrypt(line));                // pobiera rozsyfrowane liste z linii

        if (temp.size() != 5) {                                              // jesli linia nie zawiera 5 elementow
            continue;                                                        // przechodzi do nastepnej linii
        }
        bool condition = true;
        for (std::string cat: category) {                                    // sprawdza czy kategoria nie istnieje
            if (temp[4] == cat) {                                            // jesli istnieje
                condition = false;                                           // zmienia wartosc na false
            }
        }
        if (condition == true) {                                             // jesli kategoria nie istnieje
            category.push_back(temp[4]);                                     // dodaje kategorie do listy
        }
    }
    return category;
}

/**
 * metoda getPasswordList() pobiera liste hasel z pliku.
 */
std::vector<Password> PasswordManager::getPasswordList(std::string path) {
    std::string line;
    std::vector<Password> passwords;                                                                                              // lista hasel

    std::ifstream fileReader(path);
    if (fileReader.is_open() == false) {                                                                                          // jesli plik nie istnieje
        std::cout << "Blad podczas otwierania pliku" << std::endl;
        return passwords;                                                                                                         // zwroc pusta liste
    }

    while (fileReader.eof() == false) {                                                                                           // dopoki nie dojdzie do konca pliku
        std::vector<std::string> plikElement;                                                                                     // lista elementow pliku

        getline(fileReader, line);                                                                                         // pobierz linie z pliku
        plikElement = getRegexMatches(coder::decrypt(line));                                                              // zamien haslo na zakodowane

        if (plikElement.size() == 5) {                                                                                            // jesli linia zawiera 5 elementow
            Password el = Password(plikElement[0], plikElement[1], plikElement[2],plikElement[3], plikElement[4]); // tworz haslo
            passwords.push_back(el);                                                                                              // dodaj haslo do listy
        }
    }
    return passwords;
}

/**
 * metoda getPasswordsFileName() pobiera nazwe pliku z haslami
 */
std::string PasswordManager::getPasswordsFileName() {
    return passwordsFileName;
}

/**
 * metoda deleteCategory() usuwa kategorie z pliku
 */
void PasswordManager::deleteCategory(std::string path) {
    std::vector<Password> passwords = getPasswordList(path);
    std::vector<std::string> categories = getCategoryList(path);
    std::cout << "Wybierz kategorie do usuniecia: " << std::endl;
    int option;

    for(int i = 0; i < categories.size(); i++) {
        std::cout << i + 1 << ": " << categories[i] << std::endl;
    }

    std::cin >> option;

    for (int i = 0; i < passwords.size(); i++) {
        if (passwords[i].getCategory() == categories[option - 1])            // jesli kategoria jest taka sama jak wybrana
            passwords.erase(passwords.begin() + i);                  // usuwa haslo z listy i kategrje
    }

    std::string finalText;
    for(Password pas : passwords) {
        if(pas.getCategory() != categories[option - 1]) {
            finalText += coder::encrypt(pas.getName() + " | " + pas.getLogin() + " | " + pas.getPassword() + " | " + pas.getLink() + " | " + pas.getCategory()) + "\n";
        }
    }
    std::ofstream update(path);
    update << finalText;
    update.close();

    std::cout << "Kategoria zostala usunieta." << std::endl;
}





