#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include "Figure.hpp"
#include <cmath>

template<ScalarType T>
class Rhombus : public Figure<T> {
public:
    Rhombus() = default;
    
    Rhombus(const Point<T>& p1, const Point<T>& p2, 
            const Point<T>& p3, const Point<T>& p4) {
        this->vertices.push_back(std::make_shared<Point<T>>(p1));
        this->vertices.push_back(std::make_shared<Point<T>>(p2));
        this->vertices.push_back(std::make_shared<Point<T>>(p3));
        this->vertices.push_back(std::make_shared<Point<T>>(p4));
    }
    
    // Конструктор копирования
    Rhombus(const Rhombus& other) : Figure<T>(other) {}
    
    // Оператор присваивания
    Rhombus& operator=(const Rhombus& other) {
        Figure<T>::operator=(other);
        return *this;
    }
    
    double area() const override {
        if (this->vertices.size() != 4) return 0.0;
        double d1 = this->vertices[0]->distanceTo(*this->vertices[2]);
        double d2 = this->vertices[1]->distanceTo(*this->vertices[3]);
        return 0.5 * d1 * d2;
    }
    
    Point<T> center() const override {
        if (this->vertices.empty()) return Point<T>();
        T sumX = 0, sumY = 0;
        for (const auto& vertex : this->vertices) {
            sumX += vertex->getX();
            sumY += vertex->getY();
        }
        return Point<T>(sumX / this->vertices.size(), 
                        sumY / this->vertices.size());
    }
    
    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        this->printVertices(os);
        os << ", Area: " << area() << ", Center: " << center();
    }
    
    void input(std::istream& is) override {
        this->vertices.clear();
        std::cout << "Enter 4 vertices (x y):" << std::endl;
        for (int i = 0; i < 4; ++i) {
            T x, y;
            std::cout << "Vertex " << i + 1 << ": ";
            is >> x >> y;
            this->vertices.push_back(std::make_shared<Point<T>>(x, y));
        }
    }
};

#endif // RHOMBUS_HPP