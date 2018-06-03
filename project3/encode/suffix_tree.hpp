#pragma once

#include <string>
#include <cinttypes>
#include <ostream>

// Suffix tree is a data structure optimized for string searching and storing
// information for each string.
class suffix_tree
{
  public:
    // Create a root node
    suffix_tree() : parent(nullptr), children(), value(""), position(0) {}

    // Clean up
    ~suffix_tree();

    // Does this node has a child with the first letter of the specified value?
    bool has(char value);

    // Append to the value of this node
    void append(char value);

    // Create a new child node
    suffix_tree *add(char value, uint16_t position);

    // Expand this node at it's first character and append to value.
    suffix_tree *expand(char value, uint16_t position);

  private:
    suffix_tree *parent;
    suffix_tree *children[256];
    std::string value;
    uint16_t position;
    uint16_t count = 0;

    // Create a child node
    suffix_tree(suffix_tree *parent, std::string value, uint16_t position)
        : parent(parent), children(), value(value), position(position) {}

    // Pretty print for suffix_tree
    friend std::ostream & operator<< (std::ostream &out, suffix_tree const &t);
};

