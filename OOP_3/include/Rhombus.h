#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <array>

class Rhombus : public Figure {
private:
    std::array<std::pair<double, double>, 4> vertices; // 4 вершины ромба

public:
    Rhombus();
    Rhombus(const std::array<std::pair<double, double>, 4>& v);

    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
};

#endif