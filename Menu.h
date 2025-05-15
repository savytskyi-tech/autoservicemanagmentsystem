#ifndef MENU_H
#define MENU_H

#include "ServiceManager.h"

class Menu {
private:
    ServiceManager& serviceManager;
    void displayMainMenu() const;
public:
    Menu(ServiceManager& sm);
    void run();
};

#endif // MENU_H