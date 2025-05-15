#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class ServiceManager {
private:
    std::vector<Client> clients;
    std::vector<Car> cars;
    std::vector<Repair> repairs;
    std::vector<Part> partsInventory;

    int nextClientId;
    int nextCarId;
    int nextRepairId;
    int nextPartId;

    Client* findClientByIdInternal(int id);
    Car* findCarByIdInternal(int id);
    Repair* findRepairByIdInternal(int id);
    Part* findPartByIdInternal(int id); // Додано

public:
    ServiceManager();

    void addClient();
    void viewClients() const;
    void addCar();
    void viewCars() const;
    void scheduleRepair();
    void viewRepairs() const;
    void updateRepairStatus();
    void addPart();
    void viewParts() const;
    void orderPart(); // Додано
    void viewFinancials() const;
    void viewStatistics() const;
};

#endif // SERVICEMANAGER_H