#pragma once

#include <cinttypes>

class LookbackBuffer
{
    char *entries;
    uint8_t head, size;
    
    public:
        LookbackBuffer(uint8_t array_size) {
            entries = new char[array_size];
            size = array_size;
            head = 0;
        }

        ~LookbackBuffer() {
            delete[] entries;
        }

        // Add a new value to the buffer (and wipe an old one if necessary)
        void add(char value);

        // Add a new value by pointer
        void add(char *value);

        // Find what value is back from the head by some amount
        char* back(uint8_t amount);
};