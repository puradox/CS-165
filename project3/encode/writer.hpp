#pragma once

#include <vector>
#include <cinttypes>
#include "config.hpp"

struct encode_output {
    uint16_t length;
    uint16_t offset;
    std::string chars;
};

// Convert an array of tokens into bits and write those bits out to the 
// specified files.
void write(config conf, std::vector<encode_output> outputs, std::string filename);