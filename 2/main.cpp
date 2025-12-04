#include <iostream>
#include "decimal.h"

int main() {
    try {
        Decimal num1("12345");
        Decimal num2("67890");
        
        std::cout << "Number 1: " << num1.toString() << std::endl;
        std::cout << "Number 2: " << num2.toString() << std::endl;
        
        Decimal sum = num1.add(num2);
        std::cout << "Sum: " << sum.toString() << std::endl;
        
        Decimal diff = sum.subtract(num1);
        std::cout << "Sum - num1: " << diff.toString() << std::endl;
        
        std::cout << "num1 equals num2? " << (num1.equals(num2) ? "yes" : "no") << std::endl;
        std::cout << "num1 less than num2? " << (num1.lessThan(num2) ? "yes" : "no") << std::endl;
        
        Decimal num3("100");
        num3.addAssign(Decimal("50"));
        std::cout << "100 + 50 = " << num3.toString() << std::endl;
        
        num3.subtractAssign(Decimal("25"));
        std::cout << "150 - 25 = " << num3.toString() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}