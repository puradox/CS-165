#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "config.hpp"

int readInput(std::istream& in)
{
    config c;
    std::string line;

    std::cerr << c << std::endl;
    in >> line;
    std::cout << line << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        config::usage();
        return 7; // Argument list too long
    }
    else if (argc == 2)
    {
        // Input file is specified, read from the file
        std::ifstream in(argv[1]);
        if (!in)
        {
            std::cerr << "no such file " << argv[1] << std::endl;
            return 2;
        }
        return readInput(in);
    }
    else
    {
        // Input file not specified, read from stdin
        return readInput(std::cin);
    }
}
