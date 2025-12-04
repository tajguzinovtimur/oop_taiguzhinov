#ifndef DECIMAL_H
#define DECIMAL_H

#include <cstddef>
#include <string>
#include <stdexcept>

class Decimal {
private:
    unsigned char* digits;
    size_t size;
    
    void removeLeadingZeros();
    static bool isValidDigit(unsigned char ch);

public:
    Decimal();
    Decimal(const size_t& n, unsigned char ch = '0');
    Decimal(const std::string& str);
    Decimal(const Decimal& other);
    Decimal(Decimal&& other) noexcept;
    ~Decimal() noexcept;

    Decimal& operator=(const Decimal& other);
    Decimal& operator=(Decimal&& other) noexcept;

    Decimal add(const Decimal& other) const;
    Decimal subtract(const Decimal& other) const;
    
    Decimal& addAssign(const Decimal& other);
    Decimal& subtractAssign(const Decimal& other);

    bool equals(const Decimal& other) const;
    bool lessThan(const Decimal& other) const;
    bool greaterThan(const Decimal& other) const;

    size_t getSize() const;
    unsigned char getDigit(size_t index) const;
    
    std::string toString() const;
    
    static bool isValidDecimalString(const std::string& str);
};

#endif