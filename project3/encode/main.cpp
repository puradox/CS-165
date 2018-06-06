#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <iomanip>

#include "config.hpp"
#include "suffix_tree.hpp"
#include "queue.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        config::usage();
        return 1;
    }

    config c;

    for (int i = 1; i < argc - 1; i++)
        if (c.parse(argv[i]) != 0)
            return 22; // Invalid argument

    std::ofstream out(argv[argc - 1]);
    
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    suffix_tree t, *t0, *t1, *t2, *t3, *t4;

    t0 = t.add('a', 0);

    t0->append('b');
    t1 = t.add('b', 1);

    t0->append('a');
    t1->append('a');
    t2 = t.add('a', 2);

    std::cout << t << std::endl;;
    std::cout << *t0 << std::endl;;
    std::cout << *t1 << std::endl;;
    std::cout << *t2 << std::endl;;
    //std::cout << *t3 << std::endl;;
    //std::cout << *t4 << std::endl;;
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cerr << "Compressing files took a total of " << std::setprecision(10) << time_span.count() << " seconds." << std::endl;

    return 0;
}
