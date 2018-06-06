#pragma once

#include <vector>
#include <cinttypes>
#include <ostream>
#include "config.hpp"

struct encode_output {
    uint16_t length;
    uint16_t offset;
    std::string chars;

    friend std::ostream &operator<<(std::ostream &os, const encode_output &eo);
};

// Convert an array of tokens into bits and write those bits out to the
// specified files.
void write(config conf, uint64_t inChars, std::vector<encode_output> outputs);
