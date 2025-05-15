#include "DataStructures.h"

// --- Реалізація to_json/from_json ---
void to_json(json& j, const Client& c) {
    j = json{
        {"id", c.id},
        {"name", c.name},
        {"phone", c.phone},
        {"carIds", c.carIds}
    };
}
void from_json(const json& j, Client& c) {
    j.at("id").get_to(c.id);
    j.at("name").get_to(c.name);
    j.at("phone").get_to(c.phone);
    if (j.contains("carIds")) {
        j.at("carIds").get_to(c.carIds);
    } else {
        c.carIds = {};
    }
}

void to_json(json& j, const Car& car) {
    j = json{
        {"id", car.id},
        {"ownerId", car.ownerId},
        {"make", car.make},
        {"model", car.model},
        {"year", car.year},
        {"licensePlate", car.licensePlate},
        {"vin", car.vin}
    };
}
void from_json(const json& j, Car& car) {
    j.at("id").get_to(car.id);
    j.at("ownerId").get_to(car.ownerId);
    j.at("make").get_to(car.make);
    j.at("model").get_to(car.model);
    j.at("year").get_to(car.year);
    j.at("licensePlate").get_to(car.licensePlate);
    j.at("vin").get_to(car.vin);
}

void to_json(json& j, const Repair& r) {
    j = json{
        {"id", r.id},
        {"carId", r.carId},
        {"clientId", r.clientId},
        {"description", r.description},
        {"scheduledDate", r.scheduledDate},
        {"status", statusToString(r.status)},
        {"estimatedCost", r.estimatedCost},
        {"finalCost", r.finalCost}
    };
}
void from_json(const json& j, Repair& r) {
    j.at("id").get_to(r.id);
    j.at("carId").get_to(r.carId);
    j.at("clientId").get_to(r.clientId);
    j.at("description").get_to(r.description);
    j.at("scheduledDate").get_to(r.scheduledDate);
    std::string statusStr;
    j.at("status").get_to(statusStr);
    r.status = stringToStatus(statusStr);
    j.at("estimatedCost").get_to(r.estimatedCost);
    j.at("finalCost").get_to(r.finalCost);
}

void to_json(json& j, const Part& p) {
    j = json{
        {"id", p.id},
        {"name", p.name},
        {"article", p.article},
        {"quantity", p.quantity},
        {"price", p.price}
    };
}
void from_json(const json& j, Part& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);
    j.at("article").get_to(p.article);
    j.at("quantity").get_to(p.quantity);
    j.at("price").get_to(p.price);
}