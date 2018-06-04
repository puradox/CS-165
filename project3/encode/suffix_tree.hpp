#pragma once

#include <string>
#include <cinttypes>
#include <ostream>

// Suffix tree is a data structure optimized for string searching and storing
// information for each string.
class suffix_tree
{
  public:
    std::string value;
    uint16_t position;

    // Create a root node
    suffix_tree() : value(""), position(0), parent(nullptr), children() {}

    // Clean up
    ~suffix_tree();

    // Does this node has a child with the specified key?
    bool has(char key);

    // Return the child node with the specified key
    suffix_tree *get(char key);

    // Append to the value of this node
    void append(char key);

    // Create a new child node
    suffix_tree *add(char value, uint16_t position);

    // Return the amount of nodes in the suffix tree
    uint16_t size();

  private:
    suffix_tree *parent;
    suffix_tree *children[256];
    uint16_t count = 0;

    // Create a child node
    suffix_tree(suffix_tree *parent, char value, uint16_t position)
        : value{value}, position(position), parent(parent), children() {}

    // Add an existing node as a child
    void add(suffix_tree* node);

    // Pretty print for suffix_tree
    friend std::ostream & operator<< (std::ostream &out, suffix_tree const &t);
};

