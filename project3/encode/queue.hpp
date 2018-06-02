#pragma once

#include <cinttypes>
#include "suffix_tree.hpp"

struct circular_queue_node
{
    uint8_t value;
    suffix_tree *match = nullptr;
};

class circular_queue
{
    circular_queue_node *nodes;
    uint16_t head = 0;
    uint16_t tail = 0;
    uint16_t size = 0;
    uint16_t capacity;

  public:
    circular_queue(uint16_t capacity)
        : nodes(new circular_queue_node[capacity])
        , capacity(capacity)
    {
    }

    // Push adds a new value to the queue.
    void push(uint16_t value);

    // Pop processes a value from the queue.
    circular_queue_node pop();

    // Peek retrieves the next node in line.
    circular_queue_node peek();

    // Mark the previous node as the end of a match.
    void mark(suffix_tree *match);
};
