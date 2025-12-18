#include <iostream>
#include <cassert>
#include "Point.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Array.hpp"

using namespace std;

void testPoint() {
    cout << "Testing Point class..." << endl;
    
    Point<int> p1(1, 2);
    Point<int> p2(4, 6);
    
    assert(p1.getX() == 1);
    assert(p1.getY() == 2);
    assert(p1.distanceTo(p2) == 5.0); // 3-4-5 triangle
    
    cout << "Point tests passed!" << endl;
}

void testRhombus() {
    cout << "Testing Rhombus class..." << endl;
    
    // Квадрат (частный случай ромба)
    Rhombus<double> rhombus(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    double area = rhombus.area();
    assert(area > 1.99 && area < 2.01); // Площадь должна быть 2.0
    
    Point<double> center = rhombus.center();
    assert(center.getX() == 0 && center.getY() == 0);
    
    cout << "Rhombus tests passed!" << endl;
}

void testPentagon() {
    cout << "Testing Pentagon class..." << endl;
    
    // Правильный пятиугольник (примерные координаты)
    Pentagon<double> pentagon(
        Point<double>(0, 1),
        Point<double>(0.95, 0.31),
        Point<double>(0.59, -0.81),
        Point<double>(-0.59, -0.81),
        Point<double>(-0.95, 0.31)
    );
    
    double area = pentagon.area();
    assert(area > 2.37 && area < 2.38); // Примерная площадь
    
    cout << "Pentagon tests passed!" << endl;
}

void testHexagon() {
    cout << "Testing Hexagon class..." << endl;
    
    // Правильный шестиугольник
    Hexagon<double> hexagon(
        Point<double>(0, 0), 1.0  // Центр и длина стороны
    );
    
    double area = hexagon.area();
    assert(area > 2.59 && area < 2.60); // Площадь ≈ 2.598
    
    cout << "Hexagon tests passed!" << endl;
}

void testArray() {
    cout << "Testing Array template..." << endl;
    
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    assert(arr.getSize() == 3);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    
    arr.remove(1);
    assert(arr.getSize() == 2);
    assert(arr[0] == 1);
    assert(arr[1] == 3);
    
    cout << "Array tests passed!" << endl;
}

int main() {
    cout << "=== Running tests for Lab 4 ===" << endl;
    
    testPoint();
    testRhombus();
    testPentagon();
    testHexagon();
    testArray();
    
    cout << "\nAll tests passed successfully!" << endl;
    
    return 0;
}