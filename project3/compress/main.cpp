#include <iostream>
#include <string>
#include <stdexcept>

#include "config.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        Config::usage();
        return 1;
    }

    Config c;

    for (int i = 1; i < argc - 1; i++)
        if (c.parse(argv[i]) != 0)
            return 22; // Invalid argument

    std::cout << c << std::endl;
    return 0;
}
