#pragma once

#include <ostream>
#include <string>
#include <unordered_map>

using std::ostream;
using std::string;
using std::unordered_map;

#define ROOT 0 // index of the root node

class stree
{
  public:
    // There is no need to create an "edge" struct. Information about the
    // edge is stored right in the node.
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

        // Add an edge with a key and a beginning/end string index.
        void add(char key, int node);
    };

    int edge_length(int node);

    struct queue_node
    {
        char letter;
        node *suffix = nullptr;
    };

    //
    // Circular queue
    //

    queue_node *queue;
    int head = 0;
    int tail = 0;
    int size = 0;
    int capacity;

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

    stree(int capacity)
        : queue(new queue_node[capacity])
        , capacity(capacity)
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

    friend ostream& operator<<(ostream& os, const stree& dt);
};
