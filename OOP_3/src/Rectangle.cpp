#include "Rectangle.h"
#include <cmath>
#include <algorithm>

Rectangle::Rectangle() {
    vertices = {{{0,0}, {1,0}, {1,1}, {0,1}}};
}

Rectangle::Rectangle(const std::array<std::pair<double, double>, 4>& v) : vertices(v) {}

double Rectangle::area() const {
    double width = std::abs(vertices[1].first - vertices[0].first);
    double height = std::abs(vertices[2].second - vertices[1].second);
    return width * height;
}

std::pair<double, double> Rectangle::center() const {
    double cx = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first) / 4.0;
    double cy = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second) / 4.0;
    return {cx, cy};
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.first << ", " << v.second << ") ";
    }
}

void Rectangle::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v.first >> v.second;
    }
}

Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}