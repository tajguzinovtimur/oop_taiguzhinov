#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "Figure.hpp"
#include <cmath>

template<ScalarType T>
class Hexagon : public Figure<T> {
private:
    using PointPtr = std::unique_ptr<Point<T>>;
    
public:
    Hexagon() = default;
    
    // Конструктор по 6 точкам
    Hexagon(const Point<T>& p1, const Point<T>& p2, 
            const Point<T>& p3, const Point<T>& p4,
            const Point<T>& p5, const Point<T>& p6) {
        this->vertices.push_back(std::make_unique<Point<T>>(p1));
        this->vertices.push_back(std::make_unique<Point<T>>(p2));
        this->vertices.push_back(std::make_unique<Point<T>>(p3));
        this->vertices.push_back(std::make_unique<Point<T>>(p4));
        this->vertices.push_back(std::make_unique<Point<T>>(p5));
        this->vertices.push_back(std::make_unique<Point<T>>(p6));
    }
    
    // Конструктор правильного шестиугольника
    Hexagon(const Point<T>& center, double sideLength) {
        T cx = center.getX();
        T cy = center.getY();
        
        for (int i = 0; i < 6; ++i) {
            double angle = 2.0 * M_PI * i / 6.0;
            T x = cx + sideLength * std::cos(angle);
            T y = cy + sideLength * std::sin(angle);
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
    
    double area() const override {
        if (this->vertices.size() != 6) return 0.0;
        
        // Площадь по координатам вершин (метод гаусса)
        double sum = 0.0;
        for (size_t i = 0; i < 6; ++i) {
            size_t j = (i + 1) % 6;
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
        os << "Hexagon: ";
        this->printVertices(os);
        os << ", Area: " << area() << ", Center: " << center();
    }
    
    void input(std::istream& is) override {
        this->vertices.clear();
        std::cout << "Enter 6 vertices of hexagon (x y for each):" << std::endl;
        
        for (int i = 0; i < 6; ++i) {
            T x, y;
            std::cout << "Vertex " << i + 1 << ": ";
            is >> x >> y;
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
};

#endif // HEXAGON_HPP