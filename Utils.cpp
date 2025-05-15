#include "Utils.h"
#include <cstdlib> // Для system()

int getIntegerInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Error: Input a whole number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    while (value.empty() || value.find_first_not_of(' ') == std::string::npos) {
        std::cout << "Error: Input can't be empty. Try Again: ";
        std::getline(std::cin, value);
    }
    return value;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}