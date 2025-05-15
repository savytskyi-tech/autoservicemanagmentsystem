#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <vector>

// --- Структури даних ---

struct Client {
    int id;
    std::string name;
    std::string phone;
    std::vector<int> carIds; // ID автомобілів цього клієнта
};

struct Car {
    int id;
    int ownerId; // ID власника (клієнта)
    std::string make; // Марка
    std::string model; // Модель
    int year;
    std::string licensePlate; // Номерний знак
    std::string vin; // VIN-код (опціонально)
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
inline std::string statusToString(RepairStatus status) {
    switch (status) {
        case RepairStatus::SCHEDULED: return "Scheduled";
        case RepairStatus::IN_PROGRESS: return "In progress";
        case RepairStatus::WAITING_PARTS: return "Waiting parts";
        case RepairStatus::COMPLETED: return "Completed";
        case RepairStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}

struct Repair {
    int id;
    int carId;
    int clientId;
    std::string description; // Опис проблеми / робіт
    std::string scheduledDate; // Дата запису (простий рядок для прикладу)
    RepairStatus status;
    double estimatedCost; // Орієнтовна вартість
    double finalCost;     // Фінальна вартість (після завершення)
};

struct Part {
    int id;
    std::string name;
    std::string article; // Артикул
    int quantity;
    double price;
};

#endif // DATASTRUCTURES_H