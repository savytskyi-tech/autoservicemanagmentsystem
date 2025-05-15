#include "ServiceManager.h"
#include "Utils.h" // Для getIntegerInput, getStringInput
#include <iostream>
#include <iomanip> // Для setw, left, fixed, setprecision
#include <limits>  // Для numeric_limits

ServiceManager::ServiceManager()
    : nextClientId(1), nextCarId(1), nextRepairId(1), nextPartId(1) {}

Client* ServiceManager::findClientByIdInternal(int id) {
    for (auto& client : clients) {
        if (client.id == id) {
            return &client;
        }
    }
    return nullptr;
}

Car* ServiceManager::findCarByIdInternal(int id) {
    for (auto& car : cars) {
        if (car.id == id) {
            return &car;
        }
    }
    return nullptr;
}

Repair* ServiceManager::findRepairByIdInternal(int id) {
    for (auto& repair : repairs) {
        if (repair.id == id) {
            return &repair;
        }
    }
    return nullptr;
}

Part* ServiceManager::findPartByIdInternal(int id) {
    for (auto& part : partsInventory) {
        if (part.id == id) {
            return &part; // ВИПРАВЛЕНО: повертаємо адресу
        }
    }
    return nullptr;
}


void ServiceManager::addClient() {
    std::cout << "\n--- Adding new customer ---\n";
    Client newClient;
    newClient.id = nextClientId++;
    newClient.name = getStringInput("Customer's name: ");
    newClient.phone = getStringInput("Phone number: ");
    clients.push_back(newClient);
    std::cout << "Customer '" << newClient.name << "' succsessfuly added with ID " << newClient.id << std::endl;
}

void ServiceManager::viewClients() const {
    std::cout << "\n--- List of Customers ---\n";
    if (clients.empty()) {
        std::cout << "List empty!\n";
        return;
    }
    std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Name" << std::setw(20) << "Phone number" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    for (const auto& client : clients) {
        std::cout << std::left << std::setw(5) << client.id
                  << std::setw(30) << client.name
                  << std::setw(20) << client.phone << std::endl;
    }
    std::cout << std::string(55, '-') << std::endl;
}

void ServiceManager::addCar() {
    std::cout << "\n--- Adding a new car ---\n";
    if (clients.empty()) {
        std::cout << "First you need to add at least one client!\n";
        return;
    }

    viewClients();
    int ownerId = getIntegerInput("Enter the vehicle owner ID: ");

    Client* owner = findClientByIdInternal(ownerId);
    if (!owner) {
        std::cout << "Error: Customer with ID " << ownerId << " not found.\n";
        return;
    }

    Car newCar;
    newCar.id = nextCarId++;
    newCar.ownerId = ownerId;
    newCar.make = getStringInput("Brand: ");
    newCar.model = getStringInput("Model: ");
    newCar.year = getIntegerInput("Year of release: ");
    newCar.licensePlate = getStringInput("Number plate: ");
    std::cout << "VIN-code (optional, Enter to skip): ";
    std::string vin_input;
    std::getline(std::cin, vin_input);
    newCar.vin = vin_input.empty() ? "N/A" : vin_input;

    cars.push_back(newCar);
    owner->carIds.push_back(newCar.id);

    std::cout << "Car " << newCar.make << " " << newCar.model << " (ID: " << newCar.id << ") successfully added for customer '" << owner->name << "'.\n";
}

void ServiceManager::viewCars() const {
    std::cout << "\n--- Car list ---\n";
    if (cars.empty()) {
        std::cout << "Car list empty!\n";
        return;
    }
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Brand" << std::setw(15) << "Model"
              << std::setw(8) << "Year" << std::setw(15) << "Number plate" << std::setw(20) << "Owner (ID)" << std::setw(20) << "Owner (Name)" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    for (const auto& car : cars) {
        const Client* owner = nullptr;
        for(const auto& c : clients){
            if(c.id == car.ownerId){
                owner = &c;
                break;
            }
        }
        std::string ownerName = owner ? owner->name : "Unknown";
        std::cout << std::left << std::setw(5) << car.id
                  << std::setw(15) << car.make
                  << std::setw(15) << car.model
                  << std::setw(8) << car.year
                  << std::setw(15) << car.licensePlate
                  << std::setw(20) << car.ownerId
                  << std::setw(20) << ownerName << std::endl;
    }
    std::cout << std::string(100, '-') << std::endl;
}

void ServiceManager::scheduleRepair() {
    std::cout << "\n--- planning a new renovation ---\n";
    if (cars.empty()) {
        std::cout << "There are no registered vehicles to schedule repairs.\n";
        return;
    }

    viewCars();
    int carId = getIntegerInput("Enter car's ID for planning renovation ");

    Car* car = findCarByIdInternal(carId);
    if (!car) {
        std::cout << "Error: Car with ID " << carId << " not found.\n";
        return;
    }
    Client* client = findClientByIdInternal(car->ownerId);
    if (!client) {
        std::cout << "Error: Unable to find owner for auto ID " << carId << ". Check data.\n";
        return;
    }

    Repair newRepair;
    newRepair.id = nextRepairId++;
    newRepair.carId = carId;
    newRepair.clientId = car->ownerId;
    newRepair.description = getStringInput("Problem description / planned repairs: ");
    newRepair.scheduledDate = getStringInput("Desired recording date/time (e.g. '2024-08-15 10:00'):");
    newRepair.status = RepairStatus::SCHEDULED;
    newRepair.estimatedCost = 0.0;
    newRepair.finalCost = 0.0;

    repairs.push_back(newRepair);

    std::cout << "Repair (ID: " << newRepair.id << ") for car " << car->make << " " << car->model
              << " (Owner: " << client->name << ") scheduled for " << newRepair.scheduledDate << ".\n";
}

void ServiceManager::viewRepairs() const {
    std::cout << "\n--- Repair list ---\n";
    if (repairs.empty()) {
        std::cout << "Repair list empty!\n";
        return;
    }

    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Car (ID)" << std::setw(25) << "Car (Brand/Number)" << std::setw(20) << "Client (Name)"
              << std::setw(20) << "Date" << std::setw(20) << "Status" << std::setw(40) << "Description" << std::endl;
    std::cout << std::string(150, '-') << std::endl;

    for (const auto& repair : repairs) {
        const Car* car = nullptr;
        for(const auto& c_ : cars) if(c_.id == repair.carId) { car = &c_; break; }

        const Client* client = nullptr;
        for(const auto& cl_ : clients) if(cl_.id == repair.clientId) { client = &cl_; break; }

        std::string carInfo = car ? (car->make + " " + car->licensePlate) : "Unknown";
        std::string clientName = client ? client->name : "Unknown";

        std::cout << std::left << std::setw(5) << repair.id
                  << std::setw(15) << repair.carId
                  << std::setw(25) << carInfo
                  << std::setw(20) << clientName
                  << std::setw(20) << repair.scheduledDate
                  << std::setw(20) << statusToString(repair.status)
                  << std::setw(40) << repair.description.substr(0, 37) + (repair.description.length() > 37 ? "..." : "")
                  << std::endl;
    }
    std::cout << std::string(150, '-') << std::endl;
}

void ServiceManager::updateRepairStatus() {
    std::cout << "\n--- Repair status update ---\n";
    if (repairs.empty()) {
        std::cout << "There are no repairs to update the status.\n";
        return;
    }

    viewRepairs();
    int repairId = getIntegerInput("Enter repair ID for update the status: ");

    Repair* repair = findRepairByIdInternal(repairId);
    if (!repair) {
        std::cout << "Error: Repair with ID " << repairId << " not found.\n";
        return;
    }

    std::cout << "Current status: " << statusToString(repair->status) << std::endl;
    std::cout << "Choose new status\n";
    std::cout << "1. Scheduled\n";
    std::cout << "2. In progress\n";
    std::cout << "3. Waiting parts\n";
    std::cout << "4. Finished\n";
    std::cout << "5. Canceled\n";
    int choice = getIntegerInput("Your choice: ");

    RepairStatus newStatus;
    double finalCost = repair->finalCost;

    switch (choice) {
        case 1: newStatus = RepairStatus::SCHEDULED; break;
        case 2: newStatus = RepairStatus::IN_PROGRESS; break;
        case 3: newStatus = RepairStatus::WAITING_PARTS; break;
        case 4:
            newStatus = RepairStatus::COMPLETED;
            std::cout << "Enter a finalcost of repair ";
            while (!(std::cin >> finalCost) || finalCost < 0) {
                std::cout << "Error: Price incorrect. ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        case 5: newStatus = RepairStatus::CANCELLED; break;
        default:
            std::cout << "Wrong choice status.\n";
            return;
    }

    repair->status = newStatus;
    repair->finalCost = finalCost;
    std::cout << "Repair status ID " << repairId << " updated to '" << statusToString(newStatus) << "'.\n";
    if (newStatus == RepairStatus::COMPLETED) {
        std::cout << "Final cost set: " << std::fixed << std::setprecision(2) << repair->finalCost << std::endl;
    }
}

void ServiceManager::addPart() {
    std::cout << "\n--- Adding parts on warehouse ---\n";
    Part newPart;
    newPart.id = nextPartId++;
    newPart.name = getStringInput("Name of the part: ");
    newPart.article = getStringInput("Article");
    newPart.quantity = getIntegerInput("Quantity in stock: ");
    std::cout << "Price: ";
    double price;
    while (!(std::cin >> price) || price < 0) {
        std::cout << "Error: Incorrect price ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    newPart.price = price;

    partsInventory.push_back(newPart);
    std::cout << "Part '" << newPart.name << "' (ID: " << newPart.id << ") successefuly added to warehouse.\n";
}

void ServiceManager::viewParts() const {
    std::cout << "\n--- Parts warehouse ---\n";
    if (partsInventory.empty()) {
        std::cout << "Warehouse empty\n";
        return;
    }
    std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Name" << std::setw(20) << "Article"
              << std::setw(10) << "Quantity" << std::setw(15) << "Price (unit.)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& part : partsInventory) {
        std::cout << std::left << std::setw(5) << part.id
                  << std::setw(30) << part.name
                  << std::setw(20) << part.article
                  << std::setw(10) << part.quantity
                  << std::setw(15) << part.price << std::endl;
    }
    std::cout << std::defaultfloat;
    std::cout << std::string(80, '-') << std::endl;
}

void ServiceManager::orderPart() {
    std::cout << "\n--- Order Spare Parts ---\n";
    if (partsInventory.empty()) {
        std::cout << "Parts inventory is empty. Add parts before ordering.\n";
        return;
    }

    viewParts(); // Показати список запчастин для вибору

    int partId = getIntegerInput("Enter ID of the part to order: ");
    Part* partToOrder = findPartByIdInternal(partId);

    if (!partToOrder) {
        std::cout << "Error: Part with ID " << partId << " not found.\n";
        return;
    }

    std::cout << "Selected part: " << partToOrder->name
              << " (Article: " << partToOrder->article
              << ", Current stock: " << partToOrder->quantity << ")\n";

    int quantityOrdered = getIntegerInput("Enter quantity to order: ");

    if (quantityOrdered <= 0) {
        std::cout << "Error: Order quantity must be a positive number.\n";
        return;
    }

    partToOrder->quantity += quantityOrdered;

    std::cout << "Successfully ordered " << quantityOrdered << " units of '" << partToOrder->name << "'.\n";
    std::cout << "New stock quantity: " << partToOrder->quantity << std::endl;
    std::cout << "Price per unit: " << std::fixed << std::setprecision(2) << partToOrder->price << std::endl;
    std::cout << "Total cost of this order: " << std::fixed << std::setprecision(2) << (partToOrder->price * quantityOrdered) << " UAH." << std::endl;
    std::cout << std::defaultfloat;
}


void ServiceManager::viewFinancials() const {
    std::cout << "\n--- Financial account (basic) ---\n";
    double totalCompletedRevenue = 0.0;
    int completedCount = 0;

    for(const auto& repair : repairs) {
        if (repair.status == RepairStatus::COMPLETED) {
            totalCompletedRevenue += repair.finalCost;
            completedCount++;
        }
    }

    if (completedCount > 0) {
        std::cout << "Total amount for completed repairs: " << std::fixed << std::setprecision(2) << totalCompletedRevenue << " UAH.\n";
        std::cout << "Number of completed repairs: " << completedCount << std::endl;
    } else {
        std::cout << "There are no completed repairs yet to calculate.\n";
    }
}

void ServiceManager::viewStatistics() const {
    std::cout << "\n--- Service Statistics (Basic) ---\n";
    if (repairs.empty()) {
        std::cout << "There is no data for stats\n";
        return;
    }

    int scheduled = 0, inProgress = 0, waiting = 0, completed = 0, cancelled = 0;
    for(const auto& repair : repairs) {
        switch (repair.status) {
            case RepairStatus::SCHEDULED: scheduled++; break;
            case RepairStatus::IN_PROGRESS: inProgress++; break;
            case RepairStatus::WAITING_PARTS: waiting++; break;
            case RepairStatus::COMPLETED: completed++; break;
            case RepairStatus::CANCELLED: cancelled++; break;
        }
    }
    std::cout << "Total number of repairs: " << repairs.size() << std::endl;
    std::cout << "----------------------------------\n";
    std::cout << "Status              | Count\n";
    std::cout << "----------------------------------\n";
    std::cout << std::left << std::setw(19) << "Scheduled" << "| " << scheduled << std::endl;
    std::cout << std::left << std::setw(19) << "In Progress" << "| " << inProgress << std::endl;
    std::cout << std::left << std::setw(19) << "Waiting for Parts" << "| " << waiting << std::endl;
    std::cout << std::left << std::setw(19) << "Completed" << "| " << completed << std::endl;
    std::cout << std::left << std::setw(19) << "Cancelled" << "| " << cancelled << std::endl;
    std::cout << "----------------------------------\n";
}