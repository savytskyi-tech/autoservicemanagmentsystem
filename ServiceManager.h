#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "DataStructures.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class ServiceManager {
private:
    std::string dataFilePath;

    std::vector<Client> clients;
    std::vector<Car> cars;
    std::vector<Repair> repairs;
    std::vector<Part> partsInventory;

    int nextClientId;
    int nextCarId;
    int nextRepairId;
    int nextPartId;

    void loadDataFromFile();
    void saveDataToFile() const;

    int generateNextClientId();
    int generateNextCarId();
    int generateNextRepairId();
    int generateNextPartId();

    // find...ByIdInternal методи тепер const
    const Client* findClientByIdInternal(int id) const;
    const Car* findCarByIdInternal(int id) const;
    const Repair* findRepairByIdInternal(int id) const; // Зробимо всі const для уніфікації
    const Part* findPartByIdInternal(int id) const;     // Зробимо всі const для уніфікації

public:
    ServiceManager(const std::string& filePath = "autoservice_data.json");
    ~ServiceManager();

    void addClient();
    void viewClients() const;
    void addCar();
    void viewCars() const;
    void scheduleRepair();
    void viewRepairs() const;
    void updateRepairStatus();
    void addPart();
    void viewParts() const;
    void orderPart();
    void viewFinancials() const;
    void viewStatistics() const;
};

#endif // SERVICEMANAGER_H