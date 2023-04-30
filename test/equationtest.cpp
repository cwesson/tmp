
#include "tmp/equation/equation.h"
using namespace tmp::equation;

#include <iostream>

int main() {
    symbol<double> x("x");
    symbol<double> y("y");

    auto f = x + y;
    auto g = x * y;

    x = 4;
    y = 7;
    std::cout << f << "=" << f() << std::endl;
    std::cout << g << "=" << g() << std::endl;

    auto deriv = f.derivative(x);
    std::cout << "d x+y /dx = " << deriv << " (should be 1)" << std::endl;
    auto dg = g.derivative(x);
    std::cout << "d x*y /dx = " << dg << " (should be y)" << std::endl;

    return 0;
}
