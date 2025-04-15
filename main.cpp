#include <iostream>
#include <vector>
#include <string>
#include <limits> // Для numeric_limits
#include <iomanip> // Для setw, left
#include <ctime>   // Для отримання поточної дати/часу (спрощено)
#include <windows.h>
#include <locale>



using namespace std;

// --- Структури даних ---

struct Client {
    int id;
    string name;
    string phone;
    vector<int> carIds; // ID автомобілів цього клієнта
};

struct Car {
    int id;
    int ownerId; // ID власника (клієнта)
    string make; // Марка
    string model; // Модель
    int year;
    string licensePlate; // Номерний знак
    string vin; // VIN-код (опціонально)
};

// Статуси ремонту
enum class RepairStatus {
    SCHEDULED,    // Заплановано
    IN_PROGRESS,  // В роботі
    WAITING_PARTS,// Очікує запчастини
    COMPLETED,    // Завершено
    CANCELLED     // Скасовано
};

// Функція для перетворення статусу в рядок
string statusToString(RepairStatus status) {
    switch (status) {
        case RepairStatus::SCHEDULED: return "Scheduled";
        case RepairStatus::IN_PROGRESS: return "In progress";
        case RepairStatus::WAITING_PARTS: return "Waiting parts";
        case RepairStatus::COMPLETED: return "Completed";
        case RepairStatus::CANCELLED: return "Cancelled";
        default: return "unknown";
    }
}

struct Repair {
    int id;
    int carId;
    int clientId;
    string description; // Опис проблеми / робіт
    string scheduledDate; // Дата запису (простий рядок для прикладу)
    RepairStatus status;
    double estimatedCost; // Орієнтовна вартість
    double finalCost;     // Фінальна вартість (після завершення)
    // Можна додати список використаних запчастин
};

struct Part {
    int id;
    string name;
    string article; // Артикул
    int quantity;
    double price;
};

// --- Глобальні сховища даних (для простоти) ---
vector<Client> clients;
vector<Car> cars;
vector<Repair> repairs;
vector<Part> partsInventory; // Склад запчастин

int nextClientId = 1;
int nextCarId = 1;
int nextRepairId = 1;
int nextPartId = 1;

// --- Допоміжні функції ---

// Безпечне зчитування цілого числа
int getIntegerInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Error: Input a whole number: ";
        cin.clear(); // Скидаємо прапорець помилки
        // Пропускаємо некоректний ввід до кінця рядка
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистити буфер після числа
    return value;
}

// Зчитування рядка
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    // Проста перевірка на порожній рядок (можна зробити надійнішою)
    while (value.empty() || value.find_first_not_of(' ') == string::npos) {
         cout << "Error: Input can't  be empty. Try Again: ";
         getline(cin, value);
    }
    return value;
}

// Пошук клієнта за ID
Client* findClientById(int id) {
    for (auto& client : clients) {
        if (client.id == id) {
            return &client;
        }
    }
    return nullptr; // Не знайдено
}

// Пошук автомобіля за ID
Car* findCarById(int id) {
    for (auto& car : cars) {
        if (car.id == id) {
            return &car;
        }
    }
    return nullptr; // Не знайдено
}

// Пошук ремонту за ID
Repair* findRepairById(int id) {
    for (auto& repair : repairs) {
        if (repair.id == id) {
            return &repair;
        }
    }
    return nullptr;
}


// --- Функції основного меню ---

void addClient() {
    cout << "\n--- Adding new customer ---\n";
    Client newClient;
    newClient.id = nextClientId++;
    newClient.name = getStringInput("Customer's name: ");
    newClient.phone = getStringInput("Phone number: ");
    clients.push_back(newClient);
    cout << "Customer '" << newClient.name << "' succsessfuly added with ID " << newClient.id << endl;
}

void viewClients() {
    cout << "\n--- List of Customers ---\n";
    if (clients.empty()) {
        cout << "List empty!\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(30) << "Name" << setw(20) << "Phone number" << endl;
    cout << string(55, '-') << endl;
    for (const auto& client : clients) {
        cout << left << setw(5) << client.id
             << setw(30) << client.name
             << setw(20) << client.phone << endl;
    }
    cout << string(55, '-') << endl;
}

void addCar() {
    cout << "\n--- Adding a new car ---\n";
    if (clients.empty()) {
        cout << "First you need to add at least one client!\n";
        return;
    }

    viewClients(); // Показати список клієнтів для вибору власника
    int ownerId = getIntegerInput("Enter the vehicle owner ID: ");

    Client* owner = findClientById(ownerId);
    if (!owner) {
        cout << "Error: Customer with ID " << ownerId << " not found.\n";
        return;
    }

    Car newCar;
    newCar.id = nextCarId++;
    newCar.ownerId = ownerId;
    newCar.make = getStringInput("Brand: ");
    newCar.model = getStringInput("Model: ");
    newCar.year = getIntegerInput("Year of release: ");
    newCar.licensePlate = getStringInput("Number plate: ");
    newCar.vin = getStringInput("VIN-код (optional, Enter to skip): ");
    if (newCar.vin.empty()) newCar.vin = "N/A";


    cars.push_back(newCar);
    owner->carIds.push_back(newCar.id); // Додати ID авто до списку клієнта

    cout << "Car " << newCar.make << " " << newCar.model << " (ID: " << newCar.id << ") successfully added for customer '" << owner->name << "'.\n";
}

void viewCars() {
    cout << "\n--- Car list ---\n";
    if (cars.empty()) {
        cout << "Car list empty!\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Brand" << setw(15) << "Model"
         << setw(8) << "Year" << setw(15) << "Number plate" << setw(20) << "Owner (ID)" << setw(20) << "Owner (Name)" << endl;
    cout << string(100, '-') << endl;
    for (const auto& car : cars) {
        Client* owner = findClientById(car.ownerId);
        string ownerName = owner ? owner->name : "Unknown";
        cout << left << setw(5) << car.id
             << setw(15) << car.make
             << setw(15) << car.model
             << setw(8) << car.year
             << setw(15) << car.licensePlate
             << setw(20) << car.ownerId
             << setw(20) << ownerName << endl;
    }
    cout << string(100, '-') << endl;
}


void scheduleRepair() {
     cout << "\n--- planning a new renovation ---\n";
    if (cars.empty()) {
        cout << "There are no registered vehicles to schedule repairs.\n";
        return;
    }

    viewCars(); // Показати список авто для вибору
    int carId = getIntegerInput("Enter car's ID for planning renovation ");

    Car* car = findCarById(carId);
    if (!car) {
        cout << "Error: Car with ID " << carId << " not found.\n";
        return;
    }
     Client* client = findClientById(car->ownerId);
     if (!client) {
        cout << "Error: Unable to find owner for auto ID " << carId << ". Check data.\n";
        return;
     }


    Repair newRepair;
    newRepair.id = nextRepairId++;
    newRepair.carId = carId;
    newRepair.clientId = car->ownerId;
    newRepair.description = getStringInput("Problem description / planned repairs: ");
    newRepair.scheduledDate = getStringInput("Desired recording date/time (e.g. '2024-08-15 10:00'):"); // Простий рядок
    newRepair.status = RepairStatus::SCHEDULED; // Початковий статус
    newRepair.estimatedCost = 0.0; // Можна додати запит на орієнтовну вартість
    newRepair.finalCost = 0.0;

    repairs.push_back(newRepair);

    cout << "Repair (ID: " << newRepair.id << ") for car " << car->make << " " << car->model
         << " (Owner: " << client->name << ") scheduled for " << newRepair.scheduledDate << ".\n";
}

void viewRepairs() {
    cout << "\n--- Repair list ---\n";
    if (repairs.empty()) {
        cout << "Repair list empty!\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(15) << "Car (ID)" << setw(25) << "Car (Brand/Number)" << setw(20) << "Client (Name)"
         << setw(20) << "Date" << setw(20) << "Status" << setw(40) << "Description" << endl;
    cout << string(150, '-') << endl;

    for (const auto& repair : repairs) {
        Car* car = findCarById(repair.carId);
        Client* client = findClientById(repair.clientId);
        string carInfo = car ? (car->make + " " + car->licensePlate) : "Unknown";
        string clientName = client ? client->name : "Unknown";

        cout << left << setw(5) << repair.id
             << setw(15) << repair.carId
             << setw(25) << carInfo
             << setw(20) << clientName
             << setw(20) << repair.scheduledDate
             << setw(20) << statusToString(repair.status)
             << setw(40) << repair.description.substr(0, 37) + (repair.description.length() > 37 ? "..." : "")
             << endl;
    }
    cout << string(150, '-') << endl;
}

void updateRepairStatus() {
    cout << "\n--- Repair status update ---\n";
    if (repairs.empty()) {
        cout << "There are no repairs to update the status.\n";
        return;
    }

    viewRepairs(); // Показати ремонти
    int repairId = getIntegerInput("Enter repair ID for update the status: ");

    Repair* repair = findRepairById(repairId);
    if (!repair) {
        cout << "Error: Repair with ID " << repairId << " not found.\n";
        return;
    }

    cout << "Current status: " << statusToString(repair->status) << endl;
    cout << "Choose new status\n";
    cout << "1. Scheduled\n";
    cout << "2. In progress\n";
    cout << "3. Waiting parts\n";
    cout << "4. Finished\n";
    cout << "5. Canceled\n";
    int choice = getIntegerInput("Your choice: ");

    RepairStatus newStatus;
    double finalCost = repair->finalCost; // Зберегти поточну фінальну вартість

    switch (choice) {
        case 1: newStatus = RepairStatus::SCHEDULED; break;
        case 2: newStatus = RepairStatus::IN_PROGRESS; break;
        case 3: newStatus = RepairStatus::WAITING_PARTS; break;
        case 4:
            newStatus = RepairStatus::COMPLETED;
            cout << "Enter a finalcost of repair ";
             while (!(cin >> finalCost) || finalCost < 0) {
                cout << "Error: Price incorrect. ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистити буфер
            break;
        case 5: newStatus = RepairStatus::CANCELLED; break;
        default:
            cout << "Wrong choice status.\n";
            return;
    }

    repair->status = newStatus;
    repair->finalCost = finalCost; // Оновити фінальну вартість (особливо для статусу COMPLETED)
    cout << "Repair status ID " << repairId << " updated to '" << statusToString(newStatus) << "'.\n";
     if (newStatus == RepairStatus::COMPLETED) {
        cout << "Final cost set: " << fixed << setprecision(2) << repair->finalCost << endl;
     }
}


// --- Функції для запчастин (дуже базові) ---
void addPart() {
    cout << "\n--- Adding parts on warehouse ---\n";
    Part newPart;
    newPart.id = nextPartId++;
    newPart.name = getStringInput("Name of the part: ");
    newPart.article = getStringInput("Article");
    newPart.quantity = getIntegerInput("Quantity in stock: ");
     cout << "Price: ";
     double price;
     while (!(cin >> price) || price < 0) {
         cout << "Error: Incorrect price ";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистити буфер
     newPart.price = price;


    partsInventory.push_back(newPart);
    cout << "Part '" << newPart.name << "' (ID: " << newPart.id << ") successefuly added to warehouse.\n";
}

void viewParts() {
     cout << "\n--- Parts warehouse ---\n";
    if (partsInventory.empty()) {
        cout << "Warehouse empty\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(30) << "Name" << setw(20) << "Article"
         << setw(10) << "Quantity" << setw(15) << "Price (unit.)" << endl;
    cout << string(80, '-') << endl;
    cout << fixed << setprecision(2); // Встановити точність для цін
    for (const auto& part : partsInventory) {
        cout << left << setw(5) << part.id
             << setw(30) << part.name
             << setw(20) << part.article
             << setw(10) << part.quantity
             << setw(15) << part.price << endl;
    }
     cout << defaultfloat; // Повернути стандартне форматування
    cout << string(80, '-') << endl;
}

// --- Фінанси та статистика (дуже базові) ---

void viewFinancials() {
    cout << "\n--- Financial account (basic) ---\n";
    double totalCompletedRevenue = 0.0;
    int completedCount = 0;

    for(const auto& repair : repairs) {
        if (repair.status == RepairStatus::COMPLETED) {
            totalCompletedRevenue += repair.finalCost;
            completedCount++;
        }
    }

    if (completedCount > 0) {
         cout << "Total amount for completed repairs: " << fixed << setprecision(2) << totalCompletedRevenue << " UAH.\n";
         cout << "Number of completed repairs: " << completedCount << endl;
    } else {
        cout << "There are no completed repairs yet to calculate.\n";
    }
    // Тут можна додати облік витрат на запчастини, зарплати тощо.
}

void viewStatistics() {
    cout << "\n--- Service Statistics (Basic) ---\n";
    if (repairs.empty()) {
        cout << "There is no data for stats\n";
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
    cout << "Total number of repairs: " << repairs.size() << endl;
    cout << "----------------------------------\n";
    cout << "Status              | Count\n";
    cout << "----------------------------------\n";
    cout << left << setw(19) << "Scheduled" << "| " << scheduled << endl;
    cout << left << setw(19) << "In Progress" << "| " << inProgress << endl;
    cout << left << setw(19) << "Waiting for Parts" << "| " << waiting << endl;
    cout << left << setw(19) << "Completed" << "| " << completed << endl;
    cout << left << setw(19) << "Cancelled" << "| " << cancelled << endl;
    cout << "----------------------------------\n";

     // Можна додати статистику по типах робіт, якщо розширити структуру Repair
}


// --- Головне меню ---
void displayMenu() {
    cout << "\n========= Auto Service Management Menu =========\n";
    cout << "--- Clients and Vehicles ---\n";
    cout << "1. Add a client\n";
    cout << "2. View client list\n";
    cout << "3. Add a vehicle\n";
    cout << "4. View vehicle list\n";
    cout << "--- Repairs ---\n";
    cout << "5. Register vehicle for repair\n";
    cout << "6. View repair list\n";
    cout << "7. Update repair status\n";
    cout << "--- Spare Parts ---\n";
    cout << "8. Add spare part to inventory\n";
    cout << "9. View parts inventory\n";
    cout << "10. Order parts (not implemented)\n";
    cout << "--- Accounting and Statistics ---\n";
    cout << "11. View financial report (basic)\n";
    cout << "12. View service statistics (basic)\n";
    cout << "--------------------------------------\n";
    cout << "0. Exit\n";
    cout << "======================================\n";
}


int main() {
    system("chcp 65001");
    // Встановлюємо локаль для коректного відображення українських літер в консолі
    // Може знадобитися налаштування самої консолі (напр. chcp 65001 в Windows cmd)

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_CTYPE, "Ukr");
    int choice;
    do {
        displayMenu();
        choice = getIntegerInput("Your choice: ");

        switch (choice) {
            case 1: addClient(); break;
            case 2: viewClients(); break;
            case 3: addCar(); break;
            case 4: viewCars(); break;
            case 5: scheduleRepair(); break;
            case 6: viewRepairs(); break;
            case 7: updateRepairStatus(); break;
            case 8: addPart(); break;
            case 9: viewParts(); break;
            case 10: cout << "Function 'spare parts ordering' is not yet realized \n"; break;
            case 11: viewFinancials(); break;
            case 12: viewStatistics(); break;
            case 0: cout << "Ends program.\n"; break;
            default: cout << "Wrong choice. Try again.\n"; break;
        }
        if (choice != 0) {
             cout << "\nPress Enter to continue";
             // Очікуємо натискання Enter перед показом меню знову
             cin.get(); // Може потребувати другого cin.get() якщо попередній ввід залишив \n
             // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Гарантовано очищає буфер
        }

    } while (choice != 0);

    return 0;
}