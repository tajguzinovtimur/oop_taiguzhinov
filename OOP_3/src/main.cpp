#include <iostream>
#include <vector>
#include <memory>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Figure.h"

int main() {
    std::vector<Figure*> figures;

    std::cout << "Enter figures (1 - Rectangle, 2 - Trapezoid, 3 - Rhombus, 0 - finish):\n";
    int choice;
    while (std::cin >> choice && choice != 0) {
        Figure* fig = nullptr;
        switch (choice) {
            case 1: fig = new Rectangle(); break;
            case 2: fig = new Trapezoid(); break;
            case 3: fig = new Rhombus(); break;
            default: continue;
        }
        std::cout << "Enter 4 vertices (x y) for the figure:\n";
        std::cin >> *fig;
        figures.push_back(fig);
    }


    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": " << *figures[i]
                  << ", Center: (" << figures[i]->center().first << ", "
                  << figures[i]->center().second << ")"
                  << ", Area: " << figures[i]->area() << "\n";
    }

    std::cout << "Total area: " << totalArea(figures) << "\n";

    
    for (auto f : figures) delete f;

    return 0;
}