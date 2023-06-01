#include <iostream>
#include "Timer.h"
#include "boxplot.h"

long fibonacci(unsigned n) {
    return n < 2 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    Timer<double>::reset();
    std::cout <<fibonacci(42) << "\n";
    std::cout << Timer<double>::elapsed_minutes();
    std::vector<double> x1 = {30, 24, 8, 21, 35, 23, 23, 19, 13, 17};
    std::vector<double> x = { 0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
    size_t mas_size = x.size();
    size_t mas_size1 = x1.size();
    std::cout.precision(2);
    std::cout << std::scientific << boxplot<double>::min(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::max(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::lq(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::median(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::mean(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::uq(x, mas_size) << "\n";
    std::cout << std::scientific << boxplot<double>::stddev(x, mas_size) << "\n";
    auto outs = boxplot<double>::out(x, mas_size);
    for (auto el : outs) std::cout << el << " ";
}