#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "config.hpp"

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

    std::cout << c << std::endl;
    return 0;
}
