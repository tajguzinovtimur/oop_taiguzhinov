#include "Pentagon.hpp"


template class Pentagon<int>;
template class Pentagon<float>;
template class Pentagon<double>;


template<ScalarType T>
Pentagon<T>::Pentagon() = default;

template<ScalarType T>
Pentagon<T>::Pentagon(const Point<T>& p1, const Point<T>& p2, 
                     const Point<T>& p3, const Point<T>& p4,
                     const Point<T>& p5) {
    this->vertices.push_back(std::make_unique<Point<T>>(p1));
    this->vertices.push_back(std::make_unique<Point<T>>(p2));
    this->vertices.push_back(std::make_unique<Point<T>>(p3));
    this->vertices.push_back(std::make_unique<Point<T>>(p4));
    this->vertices.push_back(std::make_unique<Point<T>>(p5));
}

template<ScalarType T>
double Pentagon<T>::area() const {
    if (this->vertices.size() != 5) return 0.0;
    
    double sum = 0.0;
    for (size_t i = 0; i < 5; ++i) {
        size_t j = (i + 1) % 5;
        sum += this->vertices[i]->getX() * this->vertices[j]->getY();
        sum -= this->vertices[j]->getX() * this->vertices[i]->getY();
    }
    
    return std::abs(sum) / 2.0;
}

template<ScalarType T>
Point<T> Pentagon<T>::center() const {
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
void Pentagon<T>::print(std::ostream& os) const {
    os << "Pentagon: ";
    this->printVertices(os);
    os << ", Area: " << area() << ", Center: " << center();
}

template<ScalarType T>
void Pentagon<T>::input(std::istream& is) {
    this->vertices.clear();
    std::cout << "Enter 5 vertices of pentagon (x y for each):" << std::endl;
    
    for (int i = 0; i < 5; ++i) {
        T x, y;
        std::cout << "Vertex " << i + 1 << ": ";
        is >> x >> y;
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}