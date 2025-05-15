#include "Menu.h"
#include "ServiceManager.h"
#include <iostream>
#include <windows.h>
#include <locale>
#include <clocale>
#include <exception>

int main() {
    if (!SetConsoleCP(1251)) {
        std::cerr << "Warning: Failed to set console input codepage to 1251." << std::endl;
    }
    if (!SetConsoleOutputCP(1251)) {
        std::cerr << "Warning: Failed to set console output codepage to 1251." << std::endl;
    }
    try {
        std::locale::global(std::locale(""));
        std::cout.imbue(std::locale(""));
        std::cin.imbue(std::locale(""));
    } catch (const std::runtime_error& e) {
        std::cerr << "Warning: Could not set C++ locale to system default: " << e.what() << std::endl;
    }
    if (setlocale(LC_ALL, "") == nullptr) {
        std::cerr << "Warning: setlocale(LC_ALL, \"system default\") failed." << std::endl;
    }

    try {
        ServiceManager serviceManager("autoservice_data.json");
        Menu menu(serviceManager);
        std::cout << "\n--- Starting application ---\n" << std::endl;
        menu.run();
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.get();
        return 1;
    } catch (...) {
        std::cerr << "An unknown critical error occurred." << std::endl;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}