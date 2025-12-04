#include "decimal.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>

void Decimal::removeLeadingZeros() {
    while (size > 1 && digits[size - 1] == '0') {
        --size;
    }
}

bool Decimal::isValidDigit(unsigned char ch) {
    return ch >= '0' && ch <= '9';
}

Decimal::Decimal() : digits(new unsigned char[1]{'0'}), size(1) {}

Decimal::Decimal(const size_t& n, unsigned char ch) : size(n) {
    if (n == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    
    if (!isValidDigit(ch)) {
        throw std::invalid_argument("Invalid decimal digit");
    }
    
    digits = new unsigned char[n];
    std::fill_n(digits, n, ch);
    removeLeadingZeros();
}

Decimal::Decimal(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("String cannot be empty");
    }
    
    for (char ch : str) {
        if (!isValidDigit(ch)) {
            throw std::invalid_argument("String contains non-digit characters");
        }
    }
    
    size = str.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        digits[i] = str[size - 1 - i];
    }
    
    removeLeadingZeros();
}

Decimal::Decimal(const Decimal& other) : size(other.size) {
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);
}

Decimal::Decimal(Decimal&& other) noexcept 
    : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

Decimal::~Decimal() noexcept {
    delete[] digits;
}

Decimal& Decimal::operator=(const Decimal& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new unsigned char[size];
        std::copy(other.digits, other.digits + size, digits);
    }
    return *this;
}

Decimal& Decimal::operator=(Decimal&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        size = other.size;
        other.digits = nullptr;
        other.size = 0;
    }
    return *this;
}

Decimal Decimal::add(const Decimal& other) const {
    size_t maxSize = std::max(size, other.size);
    unsigned char* resultDigits = new unsigned char[maxSize + 1];
    
    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int a = (i < size) ? (digits[i] - '0') : 0;
        int b = (i < other.size) ? (other.digits[i] - '0') : 0;
        int sum = a + b + carry;
        
        resultDigits[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    
    if (carry > 0) {
        resultDigits[maxSize] = carry + '0';
        ++maxSize;
    }
    
    Decimal result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = maxSize;
    result.removeLeadingZeros();
    
    return result;
}

Decimal Decimal::subtract(const Decimal& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Minuend must be greater than or equal to subtrahend");
    }
    
    unsigned char* resultDigits = new unsigned char[size];
    int borrow = 0;
    
    for (size_t i = 0; i < size; ++i) {
        int a = digits[i] - '0';
        int b = (i < other.size) ? (other.digits[i] - '0') : 0;
        int diff = a - b - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        resultDigits[i] = diff + '0';
    }
    
    Decimal result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = size;
    result.removeLeadingZeros();
    
    return result;
}

Decimal& Decimal::addAssign(const Decimal& other) {
    *this = this->add(other);
    return *this;
}

Decimal& Decimal::subtractAssign(const Decimal& other) {
    *this = this->subtract(other);
    return *this;
}

bool Decimal::equals(const Decimal& other) const {
    if (size != other.size) return false;
    
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Decimal::lessThan(const Decimal& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Decimal::greaterThan(const Decimal& other) const {
    if (size != other.size) {
        return size > other.size;
    }
    
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }
    return false;
}

size_t Decimal::getSize() const {
    return size;
}

unsigned char Decimal::getDigit(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return digits[index];
}

std::string Decimal::toString() const {
    std::string result;
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        result += digits[i];
    }
    return result;
}

bool Decimal::isValidDecimalString(const std::string& str) {
    if (str.empty()) return false;
    
    for (char ch : str) {
        if (!isValidDigit(ch)) {
            return false;
        }
    }
    return true;
}