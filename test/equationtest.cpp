
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
    std::cout << "d " << f << " /dx = " << deriv << " (should be 1)" << std::endl;
    auto dg = g.derivative(x);
    std::cout << "d " << g << " /dx = " << dg << " (should be y)" << std::endl;

    auto h = constant<double>(2) * x * y;
    std::cout << h << "=" << h() << std::endl;
    auto dh = h.derivative(x);
    std::cout << "d " << h << " /dx = " << dh << " (should be 2y)" << std::endl;

    auto i = x - y;
    std::cout << i << "=" << i() << std::endl;
    auto di = i.derivative(y);
    std::cout << "d " << i << " /dx = " << di << " (should be -1)" << std::endl;


    return 0;
}
