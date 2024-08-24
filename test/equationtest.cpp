
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

    std::cout << "d " << x << " /dx = " << x.derivative(x) << " (should be 1)" << std::endl;

    auto deriv = f.derivative(x);
    std::cout << "d " << f << " /dx = " << deriv << " (should be 1)" << std::endl;
    auto dg = g.derivative(x);
    std::cout << "d " << g << " /dx = " << dg << " (should be y)" << std::endl;

    auto h = 2.0_sym * x * y;
    std::cout << h << "=" << h() << std::endl;
    auto dh = h.derivative(x);
    std::cout << "d " << h << " /dx = " << dh << " (should be 2y)" << std::endl;

    auto i = x - y;
    std::cout << i << "=" << i() << std::endl;
    auto di = i.derivative(y);
    std::cout << "d " << i << " /dy = " << di << " (should be -1)" << std::endl;

    auto j = x.pow(2.0);
    std::cout << j << "=" << j() << std::endl;
    auto dj = j.derivative(x);
    std::cout << "d " << j << " /dx = " << dj << " (should be 2x)" << std::endl;

    auto k = 1.0_sym / x;
    std::cout << k << "=" << k() << std::endl;
    auto dk = k.derivative(x);
    std::cout << "d " << k << " /dx = " << dk << " (should be -1/x^2)" << std::endl;

    auto l = x.pow(2.0) / (2.0*x + x.pow(3.0));
    std::cout << l << "=" << l() << std::endl;
    auto dl = l.derivative(x);
    std::cout << "d " << l << " /dx = " << dl << " (should be 2-x^2/(x^2+2)^2)" << std::endl;

    auto m = x.pow(4.0 * x);
    std::cout << m << "=" << m() << std::endl;
    auto dm = m.derivative(x);
    std::cout << "d " << m << " /dx = " << dm << " (should be 4x^4x ln(x)+1)" << std::endl;

    std::cout << (2.0_sym).pow(6.0_sym) << std::endl;

    return 0;
}
