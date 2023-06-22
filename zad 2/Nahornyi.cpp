#include <iostream>

#ifdef POL
    const std::string message = "Podaj liczby naturalne (0, aby zakonczyc): ";
    const std::string input = "Podaj liczbe: ";
    const std::string output = "Maksymalna suma cyfr wynosi ";
#else
    const std::string message = "Enter natural numbers (0 to finish): \n";
    const std::string input = "Enter a number:";
    const std::string output = "Max sum of digits was ";
#endif

int main() {
    std::cout << message;
    int number, max_number = 0, max_sum = 0;
    while (true) {
        std::cout << input;
        std::cin >> number;
        if (number == 0) {
            break;
        }

        int sum = 0;
        for (int n = number; n > 0; n /= 10) {
            sum += n % 10;
        }

        if (sum > max_sum) {
            max_sum = sum;
            max_number = number;
        }
    }

    std::cout << output << max_sum << " for " << max_number;
    return 0;
}