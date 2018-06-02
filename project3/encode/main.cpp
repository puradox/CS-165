#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

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

    suffix_tree t, *t0, *t1, *t2, *t3, *t4;

    t0 = t.add('a', 0);

    t1 = t.add('b', 1);
    t0->append('b');

    t2 = t1->expand('b', 2);
    std::swap(t1, t2);
    t0->append('b');

    t3 = t0->expand('a', 3);
    std::swap(t0, t3);
    t1->append('a');
    t4 = t2->add('a', 2);

    std::cout << t << std::endl;;
    std::cout << *t0 << std::endl;;
    std::cout << *t1 << std::endl;;
    std::cout << *t2 << std::endl;;
    std::cout << *t3 << std::endl;;
    std::cout << *t4 << std::endl;;

    return 0;
}
