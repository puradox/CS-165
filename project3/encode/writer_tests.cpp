#include "catch.hpp"
#include "writer.hpp"
#include <vector>

SCENARIO("writer produces correct output", "[writer]")
{
    std::vector<encode_output> outputs;
    config conf{12, 3, 3};

    outputs.push_back(encode_output{ 0, 7, "abcdefg" });
    outputs.push_back(encode_output{ 3, 4, "" });

    write(conf, 10, outputs);
}
