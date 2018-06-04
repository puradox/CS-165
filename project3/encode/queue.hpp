#pragma once

#include <cinttypes>
#include "suffix_tree.hpp"
#include "writer.hpp"

struct circular_queue_node
{
    char value;
    suffix_tree *match = nullptr;
};

class circular_queue
{
    suffix_tree tree;
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
    void push(char value);

    // Pop processes a value from the queue.
    char pop();

    // Process pops multiple values until it finds an output.
    encode_output process();

    // Returns the amount of values in the queue
    uint16_t length() { return size; }
};
