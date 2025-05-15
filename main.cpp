#include "Menu.h"
#include "ServiceManager.h"
#include <iostream>
#include <windows.h>
#include <locale>
#include <clocale>

int main() {
    // 1. Встановлюємо кодову сторінку для консолі Windows
    if (!SetConsoleCP(1251)) {
        std::cerr << "Error: Failed to set console input codepage to 1251." << std::endl;
    }
    if (!SetConsoleOutputCP(1251)) {
        std::cerr << "Error: Failed to set console output codepage to 1251." << std::endl;
    }

    // 2. Встановлюємо локаль для C++ потоків на системну за замовчуванням
    try {
        std::locale::global(std::locale(""));
        std::cout.imbue(std::locale(""));
        std::cin.imbue(std::locale(""));
        // std::cout << "Info: C++ locale set to system default." << std::endl; // Можна закоментувати, якщо не потрібен детальний лог
    } catch (const std::runtime_error& e) {
        std::cerr << "ERROR: Could not set C++ locale to system default. Error: " << e.what() << std::endl;
    }

    // 3. Встановлюємо C-стиль локаль на системну за замовчуванням
    char* cLocaleResult = setlocale(LC_ALL, "");
    if (cLocaleResult != nullptr) {
        // std::cout << "Info: C locale set to system default (resolved as: " << cLocaleResult << ")." << std::endl; // Можна закоментувати
    } else {
        std::cerr << "ERROR: setlocale(LC_ALL, \"system default\") failed." << std::endl;
    }

    ServiceManager serviceManager;
    Menu menu(serviceManager);

    std::cout << "\n--- Starting application ---\n" << std::endl;
    menu.run();

    return 0;
}