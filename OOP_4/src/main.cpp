#include <iostream>
#include <memory>
#include "Array.hpp"
#include "Rhombus.hpp"

using namespace std;

int main() {
    cout << "=== Simple Test Program ===" << endl;
    

    cout << "\nTest 1: Array with int" << endl;
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    cout << "Array size: " << arr.getSize() << endl;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    

    cout << "\nTest 2: Create a Rhombus" << endl;
    Rhombus<double> rhombus(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    cout << "Rhombus area: " << rhombus.area() << endl;
    cout << "Rhombus center: " << rhombus.center() << endl;
    

    cout << "\nTest 3: Array with shared_ptr<Figure>" << endl;
    Array<shared_ptr<Figure<double>>> figures;
    
    auto rhombusPtr = make_shared<Rhombus<double>>(rhombus);
    figures.push_back(rhombusPtr);
    
    cout << "Total figures in array: " << figures.getSize() << endl;

    cout << "\nTest 4: Output figure" << endl;
    cout << *figures[0] << endl;
    

    cout << "\nTest 5: Remove element" << endl;
    figures.remove(0);
    cout << "After removal - total figures: " << figures.getSize() << endl;
    
    return 0;
}