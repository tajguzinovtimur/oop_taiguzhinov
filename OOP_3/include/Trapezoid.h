#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <array>

class Trapezoid : public Figure {
private:
    std::array<std::pair<double, double>, 4> vertices; // 4 вершины трапеции

public:
    Trapezoid();
    Trapezoid(const std::array<std::pair<double, double>, 4>& v);

    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
};

#endif