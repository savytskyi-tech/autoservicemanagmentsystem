#ifndef MENU_H
#define MENU_H

#include "ServiceManager.h" // Потрібен для взаємодії з ServiceManager

class Menu {
private:
    ServiceManager& serviceManager; // Посилання на об'єкт ServiceManager

    void displayMainMenu() const;
    void processUserInput();

public:
    Menu(ServiceManager& sm);
    void run();
};

#endif // MENU_H