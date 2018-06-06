#pragma once

#include <iostream>
#include <cinttypes>

struct config
{
    // N - number of bits to encode window offset
    // Bounds: [9, 14]
    uint8_t N;

    // L - number of bits to encode match length
    // Bounds: [3, 4]
    uint8_t L;

    // S - number of bits to encode length of literal string
    // Bounds: [1, 5]
    uint8_t S;

    config(uint8_t N = 11, uint8_t L = 4, uint8_t S = 3) : N(N), L(L), S(S) {}

    // Prints instructions on how to use this command.
    static void usage();

    // Override how it looks when printed to the screen.
    friend std::ostream& operator<<(std::ostream& os, const config& c);

    // Parse a parameter and set the cooresponding config value.
    int parse(std::string arg);
};
