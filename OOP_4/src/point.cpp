#include "Point.hpp"


template class Point<int>;
template class Point<float>;
template class Point<double>;


template<ScalarType T>
Point<T>::Point() : x(0), y(0) {}

template<ScalarType T>
Point<T>::Point(T x, T y) : x(x), y(y) {}

template<ScalarType T>
T Point<T>::getX() const { return x; }

template<ScalarType T>
T Point<T>::getY() const { return y; }

template<ScalarType T>
void Point<T>::setX(T x) { this->x = x; }

template<ScalarType T>
void Point<T>::setY(T y) { this->y = y; }

template<ScalarType T>
double Point<T>::distanceTo(const Point<T>& other) const {
    T dx = x - other.x;
    T dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

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

template<ScalarType T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x == other.x && y == other.y;
}

template<ScalarType T>
bool Point<T>::operator!=(const Point<T>& other) const {
    return !(*this == other);
}