#ifndef POINT_HPP
#define POINT_HPP

#include <concepts>
#include <iostream>
#include <memory>
#include <cmath>

template<typename T>
concept ScalarType = std::is_scalar_v<T>;

template<ScalarType T>
class Point {
private:
    T x, y;
    
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    T getX() const { return x; }
    T getY() const { return y; }
    
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
    
    double distanceTo(const Point<T>& other) const {
        T dx = x - other.x;
        T dy = y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }
    
    // Исправляем объявления friend операторов
    template<ScalarType U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);
    
    template<ScalarType U>
    friend std::istream& operator>>(std::istream& is, Point<U>& point);
    
    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
};

template<ScalarType T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

template<ScalarType T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
    is >> point.x >> point.y;
    return is;
}

#endif // POINT_HPP