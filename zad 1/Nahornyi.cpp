#include <iostream>

int main() {
    int n;
    int min, max;
    int countMin, countMax;
    bool iteration = true;
    std::cout << "Wpisz liczbe lub 0 zeby skonczyc program" << std::endl;

    while (true) {
        std::cin >> n;

        if (n == 0) {
            break;
        }

        if (iteration) {
            min = max = n;
            countMin = countMax = 1;
            iteration = false;
        } else {
            if (n < min) {
                min = n;
                countMin = 1;
            } else if (n == min) {
                ++countMin;
            }

            if (n > max) {
                max = n;
                countMax = 1;
            } else if (n == max) {
                ++countMax;
            }
        }
    }

    std::cout << "Min = " << min << " " << countMin << " razy";
    std::cout << "\nMax = " << max << " " << countMax << " razy";
}
