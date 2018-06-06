#pragma once

#include <iostream>

#include <cmath>
#include <ostream>
#include <string>
#include <unordered_map>
#include <cinttypes>
#include <vector>
#include "config.hpp"
#include "writer.hpp"

using std::pow;
using std::ostream;
using std::string;
using std::unordered_map;
using std::vector;

#define ROOT 0 // index of the root node

class stree
{
  public:

    struct node
    {
        // [begin, end) interval specifies the edge, by which the node is
        // connected to its parent node.
        int begin;
        int end;

        // Suffix link is used for fast insertion between several suffixes.
        int suffix_link;

        // Hashmap of next suffixes
        unordered_map<char, int> next;

        node(int begin = 0, int end = 0, int suffix_link = 0)
            : begin(begin), end(end), suffix_link(suffix_link) {}

        // Get retrieves an edge from the list of edges.
        int get(char key);

        // Has checks if an edge exists with the specified key.
        bool has(char key);

        // Add an edge with a key and a node index.
        void add(char key, int node);

        // Set an edge with the specified key.
        void set(char key, int node);
    };

    int edge_length(int node);

    struct queue_node
    {
        char letter;
        node *suffix = nullptr;
    };

    //
    // Config
    //
    const int capacity;
    const int longest_match_length;
    const int longest_literal_length;

    //
    // Circular queue
    //

    queue_node *queue;
    int head = 0;
    int tail = 0;
    int size = 0;

    // Push adds a new letter to the queue.
    void push(char letter);

    // Push adds multiple letters to the queue.
    void push(string letters);

    // Pop processes a letter from the queue.
    char pop();

    //
    // Suffix tree
    //

    // Tree is an array of all of the nodes that compose of the suffix tree.
    node *tree;
    uint64_t letters_processed = 0;

    // These three values make up the active point; showing where we must start
    // inserting a new suffix.
    int active_node = ROOT;
    int active_edge = 0;
    int active_length = 0;

    // Shows the number of suffixes we must explicitly add.
    int remainder = 0;

    // Count of all the nodes
    int count = 1;

    // Track which node needs a suffix link
    int needs_link = 0;

    stree(config conf)
        : capacity(pow(2, conf.N))
        , longest_match_length(pow(2, conf.L)) // TODO(Sam): Use this
        , longest_literal_length(pow(2, conf.S))
        , queue(new queue_node[capacity])
        , tree(new node[2 * capacity])
    {
        tree[ROOT] = node(-1, -1);
    }

    ~stree();

    node &operator[](int i);

    int new_node(int start, int end = 0);

    char active_letter();

    bool walk_down(int node);

    void link(int node);

    void extend(char letter);

    // Halt execution of the suffix tree, output anything necessary.
    void halt();

    // All output results from the suffix tree
    vector<encode_output> outputs;

    // Add the appropriate encode output to the list of outputs.
    // Could either be a literal character sequence, or a relative match.
    void output(char letter = '\0');

    // Get the condensed output; multiple sequential literal outputs marged.
    vector<encode_output> get_output();

    friend ostream& operator<<(ostream& os, const stree& dt);
};
