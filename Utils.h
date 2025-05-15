#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits> // Для numeric_limits
#include <iostream> // Для cin, cout

// Безпечне зчитування цілого числа
int getIntegerInput(const std::string& prompt);

// Зчитування рядка
std::string getStringInput(const std::string& prompt);

// Очищення екрану (проста реалізація)
void clearScreen(); // Додано для можливості очищення екрану, якщо знадобиться

#endif // UTILS_H