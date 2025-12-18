#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "Figure.hpp"
#include <cmath>

template<ScalarType T>
class Pentagon : public Figure<T> {
private:
    using PointPtr = std::unique_ptr<Point<T>>;
    
public:
    Pentagon() = default;
    
    // Конструктор по 5 точкам
    Pentagon(const Point<T>& p1, const Point<T>& p2, 
             const Point<T>& p3, const Point<T>& p4,
             const Point<T>& p5) {
        this->vertices.push_back(std::make_unique<Point<T>>(p1));
        this->vertices.push_back(std::make_unique<Point<T>>(p2));
        this->vertices.push_back(std::make_unique<Point<T>>(p3));
        this->vertices.push_back(std::make_unique<Point<T>>(p4));
        this->vertices.push_back(std::make_unique<Point<T>>(p5));
    }
    
    double area() const override {
        if (this->vertices.size() != 5) return 0.0;
        
        // Площадь по координатам вершин (метод гаусса)
        double sum = 0.0;
        for (size_t i = 0; i < 5; ++i) {
            size_t j = (i + 1) % 5;
            sum += this->vertices[i]->getX() * this->vertices[j]->getY();
            sum -= this->vertices[j]->getX() * this->vertices[i]->getY();
        }
        
        return std::abs(sum) / 2.0;
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
        os << "Pentagon: ";
        this->printVertices(os);
        os << ", Area: " << area() << ", Center: " << center();
    }
    
    void input(std::istream& is) override {
        this->vertices.clear();
        std::cout << "Enter 5 vertices of pentagon (x y for each):" << std::endl;
        
        for (int i = 0; i < 5; ++i) {
            T x, y;
            std::cout << "Vertex " << i + 1 << ": ";
            is >> x >> y;
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
};

#endif // PENTAGON_HPP