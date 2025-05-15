#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <vector>
#include "json.hpp" // Переконайтеся, що цей файл доступний

// Для зручності використання
using json = nlohmann::json;

// --- Структури даних ---
struct Client {
    int id;
    std::string name;
    std::string phone;
    std::vector<int> carIds;
};

struct Car {
    int id;
    int ownerId;
    std::string make;
    std::string model;
    int year;
    std::string licensePlate;
    std::string vin;
};

enum class RepairStatus {
    SCHEDULED,
    IN_PROGRESS,
    WAITING_PARTS,
    COMPLETED,
    CANCELLED
};

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

inline RepairStatus stringToStatus(const std::string& s) {
    if (s == "Scheduled") return RepairStatus::SCHEDULED;
    if (s == "In progress") return RepairStatus::IN_PROGRESS;
    if (s == "Waiting parts") return RepairStatus::WAITING_PARTS;
    if (s == "Completed") return RepairStatus::COMPLETED;
    if (s == "Cancelled") return RepairStatus::CANCELLED;
    return RepairStatus::SCHEDULED;
}

struct Repair {
    int id;
    int carId;
    int clientId;
    std::string description;
    std::string scheduledDate;
    RepairStatus status;
    double estimatedCost;
    double finalCost;
};

struct Part {
    int id;
    std::string name;
    std::string article;
    int quantity;
    double price;
};

// --- Функції серіалізації/десеріалізації для nlohmann/json ---
void to_json(json& j, const Client& c);
void from_json(const json& j, Client& c);
void to_json(json& j, const Car& car);
void from_json(const json& j, Car& car);
void to_json(json& j, const Repair& r);
void from_json(const json& j, Repair& r);
void to_json(json& j, const Part& p);
void from_json(const json& j, Part& p);

#endif // DATASTRUCTURES_H