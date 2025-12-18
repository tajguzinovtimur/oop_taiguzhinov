#include <gtest/gtest.h>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Figure.h"
#include <sstream>

TEST(RectangleTest, Area) {
    Rectangle r;
    EXPECT_NEAR(r.area(), 1.0, 1e-6);
}

TEST(RectangleTest, Center) {
    Rectangle r;
    auto c = r.center();
    EXPECT_NEAR(c.first, 0.5, 1e-6);
    EXPECT_NEAR(c.second, 0.5, 1e-6);
}

TEST(TrapezoidTest, Area) {
    Trapezoid t;
    EXPECT_GT(t.area(), 0.0);
}

TEST(RhombusTest, Area) {
    Rhombus rh;
    EXPECT_GT(rh.area(), 0.0);
}

TEST(FigureTest, TotalArea) {
    std::vector<Figure*> figs;
    figs.push_back(new Rectangle());
    figs.push_back(new Trapezoid());
    figs.push_back(new Rhombus());

    double total = totalArea(figs);
    EXPECT_GT(total, 0.0);

    for (auto f : figs) delete f;
}