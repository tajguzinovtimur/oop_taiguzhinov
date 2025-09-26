#include "../headers/function.h"

int count_vowels(const std::string &text) {
    int count = 0;
    for (char c : text) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            count++;
        }
    }

    return count;
}