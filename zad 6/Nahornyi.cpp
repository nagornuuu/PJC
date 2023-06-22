#include <iostream>

bool checkpass(const char *pass) {

    char sign;
    int count = 0;
    int size = 0;
    bool present = false;
    bool diff = false;
    bool digit = false;
    bool bigLetter = false;
    bool smallLetter = false;
    bool non = false;
    bool length = true;

    // Check if password length is between 1 and 8 characters
    while (pass[size] != '\0') {
        size++;
        if (size > 8) {
            length = false;
            break;
        }
    }

    // Check if password contains at least two different symbols
    for (int i = 0; i < size; i++) {
        sign = pass[i];
        if (i != 0) {
            for (int j = 0; j < i; j++) {
                if (pass[j] == sign) {
                    present = true;
                    break;
                }
            }
        }
        if (!present) {
            for (int k = i + 1; k < size; k++) {
                if (pass[k] == sign) {
                    count++;
                }
            }
        }
    }

    // Check if password contains at least one digit
    for (int i = 0; i < size; i++) {
        if (pass[i] >= '0' && pass[i] <= '9') {
            digit = true;
            break;
        }
    }

    // Check if password contains at least one uppercase letter
    for (int i = 0; i < size; i++) {
        if (pass[i] >= 'A' && pass[i] <= 'Z') {
            bigLetter = true;
            break;
        }
    }

    // Check if password contains at least one lowercase letter
    for (int i = 0; i < size; i++) {
        if (pass[i] >= 'a' && pass[i] <= 'z') {
            smallLetter = true;
            break;
        }
    }

    // Check if password contains at least one non-letter and non-digit character
    for (int i = 0; i < size; i++) {
        if ((pass[i] >= '!' && pass[i] <= '/')
            || (pass[i] >= ':' && pass[i] <= '@')
            || (pass[i] >= '[' && pass[i] <= '`')
            || (pass[i] >= '{' && pass[i] <= '~')) {
            non = true;
            break;
        }
    }

    //1
    if (size > 7) {
        length = true;
    } else {
        std::cout << "Too short" << std::endl;
    }
    //2
    if (size - count >= 6) {
        diff = true;
    } else {
        std::cout << "Too few different characters" << std::endl;
    }
    //3
    if (!digit) {
        std::cout << "No digit" << std::endl;
    }
    //4
    if (!bigLetter) {
        std::cout << "No uppercase letter" << std::endl;
    }
    //5
    if (!smallLetter) {
        std::cout << "No lowercase letter" << std::endl;
    }
    //6
    if (!non) {
        std::cout << "No non-alphanumeric character" << std::endl;
    }

    return length && diff && digit && bigLetter && smallLetter && non;
}
int main() {
    using std::cout; using std::endl;
    const char* passes[] =
            {
                    "AbcDe93", "A1b:A1b>", "Ab:Acb<",
                    "abc123><", "Zorro@123", nullptr
            };
    for (int i = 0; passes[i] != nullptr; ++i) {
        cout << "checking " << passes[i] << endl;
        if (checkpass(passes[i])) cout << "OK" << endl;
        cout << endl;
    }
}
