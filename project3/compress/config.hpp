#pragma once

#include <iostream>

struct Config
{
    // N - number of bits to encode window offset
    // Bounds: [9, 14]
    int N = 11;

    // L - number of bits to encode match offset
    // Bounds: [3, 4]
    int L = 4;

    // S - number of bits to encode length of literal string
    // Bounds: [1, 5]
    int S = 3;

    // Prints instructions on how to use this command.
    static void usage();

    // Override how it looks when printed to the screen.
    friend std::ostream& operator<<(std::ostream& os, const Config& c);

    // Parse a parameter and set the cooresponding config value.
    int parse(std::string arg);
};
