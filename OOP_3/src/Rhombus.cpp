#include "Rhombus.h"
#include <cmath>
#include <algorithm>

Rhombus::Rhombus() {
    vertices = {{{0,0}, {1,1}, {2,0}, {1,-1}}};
}

Rhombus::Rhombus(const std::array<std::pair<double, double>, 4>& v) : vertices(v) {}

double Rhombus::area() const {
    double d1 = std::sqrt(std::pow(vertices[0].first - vertices[2].first, 2) +
                          std::pow(vertices[0].second - vertices[2].second, 2));
    double d2 = std::sqrt(std::pow(vertices[1].first - vertices[3].first, 2) +
                          std::pow(vertices[1].second - vertices[3].second, 2));
    return 0.5 * d1 * d2;
}

std::pair<double, double> Rhombus::center() const {
    double cx = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first) / 4.0;
    double cy = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second) / 4.0;
    return {cx, cy};
}

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.first << ", " << v.second << ") ";
    }
}

void Rhombus::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v.first >> v.second;
    }
}

Figure* Rhombus::clone() const {
    return new Rhombus(*this);
}