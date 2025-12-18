#include "Hexagon.hpp"

// Явные инстанциации
template class Hexagon<int>;
template class Hexagon<float>;
template class Hexagon<double>;

// Реализация методов (аналогично предыдущим)
template<ScalarType T>
Hexagon<T>::Hexagon() = default;

template<ScalarType T>
Hexagon<T>::Hexagon(const Point<T>& p1, const Point<T>& p2, 
                   const Point<T>& p3, const Point<T>& p4,
                   const Point<T>& p5, const Point<T>& p6) {
    this->vertices.push_back(std::make_unique<Point<T>>(p1));
    this->vertices.push_back(std::make_unique<Point<T>>(p2));
    this->vertices.push_back(std::make_unique<Point<T>>(p3));
    this->vertices.push_back(std::make_unique<Point<T>>(p4));
    this->vertices.push_back(std::make_unique<Point<T>>(p5));
    this->vertices.push_back(std::make_unique<Point<T>>(p6));
}

template<ScalarType T>
Hexagon<T>::Hexagon(const Point<T>& center, double sideLength) {
    T cx = center.getX();
    T cy = center.getY();
    
    for (int i = 0; i < 6; ++i) {
        double angle = 2.0 * M_PI * i / 6.0;
        T x = cx + sideLength * std::cos(angle);
        T y = cy + sideLength * std::sin(angle);
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template<ScalarType T>
double Hexagon<T>::area() const {
    if (this->vertices.size() != 6) return 0.0;
    
    double sum = 0.0;
    for (size_t i = 0; i < 6; ++i) {
        size_t j = (i + 1) % 6;
        sum += this->vertices[i]->getX() * this->vertices[j]->getY();
        sum -= this->vertices[j]->getX() * this->vertices[i]->getY();
    }
    
    return std::abs(sum) / 2.0;
}

template<ScalarType T>
Point<T> Hexagon<T>::center() const {
    if (this->vertices.empty()) return Point<T>();
    
    T sumX = 0, sumY = 0;
    for (const auto& vertex : this->vertices) {
        sumX += vertex->getX();
        sumY += vertex->getY();
    }
    
    return Point<T>(sumX / this->vertices.size(), 
                    sumY / this->vertices.size());
}

template<ScalarType T>
void Hexagon<T>::print(std::ostream& os) const {
    os << "Hexagon: ";
    this->printVertices(os);
    os << ", Area: " << area() << ", Center: " << center();
}

template<ScalarType T>
void Hexagon<T>::input(std::istream& is) {
    this->vertices.clear();
    std::cout << "Enter 6 vertices of hexagon (x y for each):" << std::endl;
    
    for (int i = 0; i < 6; ++i) {
        T x, y;
        std::cout << "Vertex " << i + 1 << ": ";
        is >> x >> y;
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}