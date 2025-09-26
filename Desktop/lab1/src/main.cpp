#include <iostream>
#include <string>
#include "../headers/function.h"

int main() {
    std::string input;

    std::cout << "Введите строку (только строчные и английские буквы и пробелы): ";
    std::getline(std::cin, input);

    int result = count_vowels(input);
    std::cout << "Количество гласных букв в строке: " << result << std::endl;

    return 0;
} 