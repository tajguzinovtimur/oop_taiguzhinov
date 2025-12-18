#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>

class Figure {
public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual std::pair<double, double> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual Figure* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

double totalArea(const std::vector<Figure*>& figures);

#endif