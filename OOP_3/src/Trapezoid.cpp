#include "Trapezoid.h"
#include <cmath>
#include <algorithm>

Trapezoid::Trapezoid() {
    vertices = {{{0,0}, {2,0}, {1.5,1}, {0.5,1}}};
}

Trapezoid::Trapezoid(const std::array<std::pair<double, double>, 4>& v) : vertices(v) {}

double Trapezoid::area() const {
    double a = std::abs(vertices[1].first - vertices[0].first); // нижнее основание
    double b = std::abs(vertices[2].first - vertices[3].first); // верхнее основание
    double h = std::abs(vertices[2].second - vertices[0].second); // высота
    return (a + b) * h / 2.0;
}

std::pair<double, double> Trapezoid::center() const {
    double cx = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first) / 4.0;
    double cy = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second) / 4.0;
    return {cx, cy};
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.first << ", " << v.second << ") ";
    }
}

void Trapezoid::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v.first >> v.second;
    }
}

Figure* Trapezoid::clone() const {
    return new Trapezoid(*this);
}