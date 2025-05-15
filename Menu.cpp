#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <limits>

Menu::Menu(ServiceManager& sm) : serviceManager(sm) {}

void Menu::displayMainMenu() const {
    std::cout << "\n========= Auto Service Management Menu =========\n";
    std::cout << "--- Clients and Vehicles ---\n";
    std::cout << "1. Add a client\n";
    std::cout << "2. View client list\n";
    std::cout << "3. Add a vehicle\n";
    std::cout << "4. View vehicle list\n";
    std::cout << "--- Repairs ---\n";
    std::cout << "5. Register vehicle for repair\n";
    std::cout << "6. View repair list\n";
    std::cout << "7. Update repair status\n";
    std::cout << "--- Spare Parts ---\n";
    std::cout << "8. Add spare part to inventory\n";
    std::cout << "9. View parts inventory\n";
    std::cout << "10. Order parts\n";
    std::cout << "--- Accounting and Statistics ---\n";
    std::cout << "11. View financial report (basic)\n";
    std::cout << "12. View service statistics (basic)\n";
    std::cout << "--------------------------------------\n";
    std::cout << "0. Exit\n";
    std::cout << "======================================\n";
}

void Menu::run() {
    int choice;
    do {
        displayMainMenu();
        choice = getIntegerInput("Your choice: ");
        switch (choice) {
            case 1: serviceManager.addClient(); break;
            case 2: serviceManager.viewClients(); break;
            case 3: serviceManager.addCar(); break;
            case 4: serviceManager.viewCars(); break;
            case 5: serviceManager.scheduleRepair(); break;
            case 6: serviceManager.viewRepairs(); break;
            case 7: serviceManager.updateRepairStatus(); break;
            case 8: serviceManager.addPart(); break;
            case 9: serviceManager.viewParts(); break;
            case 10: serviceManager.orderPart(); break;
            case 11: serviceManager.viewFinancials(); break;
            case 12: serviceManager.viewStatistics(); break;
            case 0: std::cout << "Ends program.\n"; break;
            default: std::cout << "Wrong choice. Try again.\n"; break;
        }
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Може знадобитися перед get()
            std::cin.get();
        }
    } while (choice != 0);
}