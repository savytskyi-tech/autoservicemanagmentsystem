#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <iostream>

int getIntegerInput(const std::string& prompt);
std::string getStringInput(const std::string& prompt);
void clearScreen();

#endif // UTILS_H