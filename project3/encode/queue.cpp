#include <stdexcept>
#include "queue.hpp"

void circular_queue::push(char value)
{
    // Check for overflow
    if (this->size == this->capacity)
        throw std::overflow_error("circular_queue::push overflow");

    // Clean old matches from the suffix_tree before overriding
    if (this->nodes[this->head].match != nullptr)
        delete this->nodes[this->head].match;

    // Add the new value
    this->nodes[this->head].value = value;
    this->nodes[this->head].match = nullptr;
    this->head = (this->head + 1) % this->capacity;
    this->size++;
}

char circular_queue::pop()
{
    // Check for underflow
    if (this->size == 0)
        throw std::underflow_error("circular_queue::pop underflow");

    // Process the current character in the queue
    char value = this->nodes[this->tail].value;
    this->tail = (this->tail + 1) % this->capacity;
    this->size--;

    return value;
}

encode_output process()
{

}
