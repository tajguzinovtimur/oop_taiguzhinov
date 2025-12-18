#include "Rhombus.hpp"


template class Rhombus<int>;
template class Rhombus<float>;
template class Rhombus<double>;


template<ScalarType T>
Rhombus<T>::Rhombus() = default;

template<ScalarType T>
Rhombus<T>::Rhombus(const Point<T>& p1, const Point<T>& p2, 
                   const Point<T>& p3, const Point<T>& p4) {
    this->vertices.push_back(std::make_unique<Point<T>>(p1));
    this->vertices.push_back(std::make_unique<Point<T>>(p2));
    this->vertices.push_back(std::make_unique<Point<T>>(p3));
    this->vertices.push_back(std::make_unique<Point<T>>(p4));
}

template<ScalarType T>
double Rhombus<T>::area() const {
    if (this->vertices.size() != 4) return 0.0;
    
    double d1 = this->vertices[0]->distanceTo(*this->vertices[2]);
    double d2 = this->vertices[1]->distanceTo(*this->vertices[3]);
    
    return 0.5 * d1 * d2;
}

template<ScalarType T>
Point<T> Rhombus<T>::center() const {
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
void Rhombus<T>::print(std::ostream& os) const {
    os << "Rhombus: ";
    this->printVertices(os);
    os << ", Area: " << area() << ", Center: " << center();
}

template<ScalarType T>
void Rhombus<T>::input(std::istream& is) {
    this->vertices.clear();
    std::cout << "Enter 4 vertices of rhombus (x y for each):" << std::endl;
    
    for (int i = 0; i < 4; ++i) {
        T x, y;
        std::cout << "Vertex " << i + 1 << ": ";
        is >> x >> y;
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template<ScalarType T>
bool Rhombus<T>::isValid() const {
    if (this->vertices.size() != 4) return false;
    
    double side1 = this->vertices[0]->distanceTo(*this->vertices[1]);
    double side2 = this->vertices[1]->distanceTo(*this->vertices[2]);
    double side3 = this->vertices[2]->distanceTo(*this->vertices[3]);
    double side4 = this->vertices[3]->distanceTo(*this->vertices[0]);
    
    const double epsilon = 1e-6;
    return std::abs(side1 - side2) < epsilon &&
           std::abs(side2 - side3) < epsilon &&
           std::abs(side3 - side4) < epsilon;
}