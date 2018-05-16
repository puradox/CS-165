#include "config.hpp"

void config::usage()
{
    std::cout << "usage: EXPAND [filename]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const config& c)
{
    os << "config { N=" << c.N << ", L=" << c.L << ", S=" << c.S << " }";
    return os;
}
