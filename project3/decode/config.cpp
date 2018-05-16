#include "config.hpp"

void Config::usage()
{
    std::cout << "usage: EXPAND [filename]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Config& c)
{
    os << "Config { N=" << c.N << ", L=" << c.L << ", S=" << c.S << " }";
    return os;
}
