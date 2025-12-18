#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "Point.hpp"
#include <memory>
#include <vector>
#include <iostream>

template<ScalarType T>
class Figure {
protected:
    // Используем shared_ptr вместо unique_ptr для возможности копирования
    using PointPtr = std::shared_ptr<Point<T>>;
    std::vector<PointPtr> vertices;
    
public:
    virtual ~Figure() = default;
    
    // Правило пяти: добавляем явные конструкторы и операторы
    Figure() = default;
    Figure(const Figure& other) {
        vertices.reserve(other.vertices.size());
        for (const auto& vertex : other.vertices) {
            vertices.push_back(std::make_shared<Point<T>>(*vertex));
        }
    }
    
    Figure(Figure&& other) noexcept = default;
    
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices.clear();
            vertices.reserve(other.vertices.size());
            for (const auto& vertex : other.vertices) {
                vertices.push_back(std::make_shared<Point<T>>(*vertex));
            }
        }
        return *this;
    }
    
    Figure& operator=(Figure&& other) noexcept = default;
    
    virtual double area() const = 0;
    virtual Point<T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;
    
    template<ScalarType U>
    friend std::ostream& operator<<(std::ostream& os, const Figure<U>& figure);
    
    template<ScalarType U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& figure);
    
    explicit virtual operator double() const {
        return area();
    }
    
    const std::vector<PointPtr>& getVertices() const { return vertices; }
    
    void printVertices(std::ostream& os) const {
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "Vertex " << i + 1 << ": " << *vertices[i];
            if (i != vertices.size() - 1) os << ", ";
        }
    }
};

template<ScalarType T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    figure.print(os);
    return os;
}

template<ScalarType T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.input(is);
    return is;
}

#endif // FIGURE_HPP