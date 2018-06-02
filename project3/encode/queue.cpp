#include "queue.hpp"

void circular_queue::push(uint16_t value)
{
    // Check for overflow
    if (this->size == this->capacity)
        throw "circular_queue overflow";

    // Clean old matches from the trie before overriding
    if (this->nodes[this->head].match != nullptr)
        delete this->nodes[this->head].match;

    // Add the new value
    this->nodes[this->head].value = value;
    this->nodes[this->head].match = nullptr;
    this->head = (this->head + 1) % this->capacity;
    this->size++;
}

uint8_t circular_queue::pop()
{
    // Check for underflow
    if (this->size == 0)
        throw "circular_queue underflow";

    // Process the current character
    uint8_t value = this->nodes[this->tail].value;
    this->tail = (this->tail + 1) % this->capacity;
    this->size--;

    return value;
}

void circular_queue::mark(suffix_tree* match)
{
    this->nodes[this->tail].match = match;
}
