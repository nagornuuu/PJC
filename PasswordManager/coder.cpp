#include "coder.h"
#include <string>

int push = 5;

/**
 * to szyfr pozycyjny - zamienia każdy znak na jego kolejną pozycję
 * szyfr Cezara
 */
std::string coder::encrypt(std::string str) {
    std::string result{};

    for (char i : str) {
        if (i >= 32 && i != 127)
            result += char(int((i + push) >= 127 ? (i + push) % 127 + 32 : (i + push)));
    }
    return result;
}

/**
 * to decrypt szyfru Cezara
 */
std::string coder::decrypt(std::string str) {
    std::string result{};
    for (char i : str) {
        if (i >= 32 && i != 127)
            result += char(int((i - push) < 32 ? (i - push) + 95 : (i - push)));
    }
    return result;
}