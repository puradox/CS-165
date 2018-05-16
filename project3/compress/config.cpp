#include "config.hpp"

void Config::usage()
{
    std::cout
        << "usage: LZ [-N] [-L] [-S] <filename>" << std::endl
        << "  -N=[9,14]  number of bits to encode window offset (default 11)" << std::endl
        << "  -L=[3,4]   number of bits to encode match length (default 4)" << std::endl
        << "  -S=[1,5]   number of bits to encode length of literal string (default 3)" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Config& c)
{
    os << "Config { N=" << c.N << ", L=" << c.L << ", S=" << c.S << " }";
    return os;
}

int Config::parse(std::string arg)
{
    std::string param = arg.substr(1, 1);
    std::string value = arg.substr(3);

    if (param == "N")
    {
        try {
            this->N = std::stoi(value);
            if (this->N < 9 || this->N > 14)
            {
                std::cerr << "N must be between 9 and 14, got " << value << std::endl;
                return 22;
            }
        } catch (std::invalid_argument e) {
            std::cerr << "N must be an integer, got " << value << std::endl;
            return 22;
        } catch (std::out_of_range e) {
            std::cerr << "N must be between 9 and 14, got " << value << std::endl;
            return 22;
        }
    }
    else if (param == "L")
    {
        try {
            this->L = std::stoi(value);
            if (this->L < 3 || this->N > 4)
            {
                std::cerr << "L must be between 3 and 4, got " << value << std::endl;
                return 22;
            }
        } catch (std::invalid_argument e) {
            std::cerr << "L must be an integer, got " << value << std::endl;
            return 22;
        } catch (std::out_of_range e) {
            std::cerr << "L must be between 3 and 4, got " << value << std::endl;
            return 22;
        }
    }
    else if (param == "S")
    {
        try {
            this->S = std::stoi(value);
            if (this->S < 1 || this->S > 5)
            {
                std::cerr << "S must be between 1 and 5, got " << value << std::endl;
                return 22;
            }
        } catch (std::invalid_argument e) {
            std::cerr << "S must be an integer, got " << value << std::endl;
            return 22;
        } catch (std::out_of_range e) {
            std::cerr << "S must be between 1 and 5, got " << value << std::endl;
            return 22;
        }
    }
    else
    {
        std::cerr << "unknown option: " << arg << std::endl << std::endl;
        Config::usage();
        return 22;
    }

    return 0;
}
