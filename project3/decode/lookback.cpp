#include <cinttypes>
#include "lookback.hpp"

void LookbackBuffer::add(char value) {
    ++head;
    entries[head] = value;
}

void LookbackBuffer::add(char *value) {
    ++head;
    entries[head] = *value;
}

char* LookbackBuffer::back(uint8_t amount) {
    int8_t index = head - amount;
    if (index < 0)
        index += size;
    
    return &entries[index];
}