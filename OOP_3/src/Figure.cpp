#include "Figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}

double totalArea(const std::vector<Figure*>& figures) {
    double total = 0.0;
    for (const auto& fig : figures) {
        total += fig->area();
    }
    return total;
}