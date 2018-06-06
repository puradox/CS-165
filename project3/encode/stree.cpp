#include <cmath>
#include <iostream>
#include <stdexcept>
#include "stree.hpp"

using std::endl;
using std::min;
using std::overflow_error;
using std::underflow_error;
using std::unordered_map;

int stree::node::get(char key)
{
    return next.at(key);
}

bool stree::node::has(char key)
{
    return next.count(key) == 1;
}

void stree::node::add(char key, int node)
{
    next.insert({key, node});
}

stree::node &stree::operator[](int i)
{
    return tree[i];
}

int stree::edge_length(int node)
{
    if (tree[node].end == 0) // open-ended
        return tail - tree[node].begin;
    else
        return min(tree[node].end, tail) - tree[node].begin;
}

void stree::push(char letter)
{
    // Check for overflow
    if (size == capacity)
        throw overflow_error("stree::push overflow");

    // Clean old suffixes from the suffix tree before overriding
    //if (queue[head].suffix != nullptr)
    //delete_node(queue[head].suffix);

    // Add the new value to the queue
    queue[head].letter = letter;
    queue[head].suffix = 0;
    head = (head + 1) % capacity;
    size++;
}

void stree::push(string letters)
{
    for (char letter : letters)
        push(letter);
}

char stree::pop()
{
    // Check for underflow
    if (size == 0)
        throw underflow_error("stree::pop underflow");

    // Process the current character in the queue
    char letter = queue[tail].letter;
    tail = (tail + 1) % capacity;
    size--;

    extend(letter);

    return letter;
}

int stree::new_node(int start, int end)
{
    int last_added = count++;
    tree[last_added] = node(start, end);
    return last_added;
}

char stree::active_letter()
{
    return queue[active_edge].letter;
}

bool stree::walk_down(int node)
{
    if (active_length < edge_length(node))
        return false;

    active_edge += edge_length(node);
    active_length -= edge_length(node);
    active_node = node;
    return true;
}

void stree::link(int node)
{
    if (needs_link)
        tree[needs_link].suffix_link = node;
    needs_link = node;
}

void stree::extend(char letter)
{
    int pos = tail - 1;
    needs_link = 0;
    remainder++;

    while (remainder > 0)
    {
        if (active_length == 0)
            active_edge = pos;

        if (tree[active_node].has(active_letter()))
        {
            // If the active node has an edge with the given letter, then
            int next = tree[active_node].get(active_letter());

            // Observation 2:
            // If at some point active length is greater or equal to the length
            // of current edge (edge length), we move our active point down
            // until edge length is strictly greater than active length.
            if (walk_down(next))
                continue;

            // Observation 1:
            // When the final suffix we need to insert is found to exist in the
            // tree already, the tree itself is not changed at all (we only
            // update the active point and remainder)
            if (queue[tree[next].begin + active_length].letter == letter)
            {
                active_length++;

                // Observation 3:
                // When the symbol we want to add to the tree is already on the
                // edge, we, according to Observation 1, update only active
                // point and reminader, leaving the tree unchanged. BUT if there
                // is an internal node marked as needing a suffix link, we must
                // connect that node with our current active node through a
                // suffix link.
                link(active_node);

                break;
            }

            int split = new_node(tree[next].begin, tree[next].begin + active_length);
            tree[active_node].add(active_letter(), split);

            int leaf = new_node(pos);
            tree[split].add(letter, leaf);
            tree[next].begin += active_length;
            tree[split].add(queue[tree[next].begin].letter, next);

            // Rule 2:
            // If we create a new internal node OR make an inserter from an
            // internal node, and this is not the first SUCH internal node at
            // current step, then we link the previous SUCH node with THIS one
            // through a suffix link.
            link(split);
        }
        else
        {
            // Otherwise, there is no edge with the matching letter
            int leaf = new_node(pos);
            tree[active_node].add(letter, leaf);
            link(active_node); // See Rule 2 above
        }

        remainder--;

        // Rule 1:
        // If after an insertion from the active node = root and the active
        // length is greater than 0, then:
        //   1. active node is not changed
        //   2. active length is decremented
        //   3. active edge is shifted right (to the first character of the next
        //      suffix we must insert)
        if (active_node == ROOT && active_length > 0)
        {
            active_length--;
            active_edge = pos - remainder + 1;
        }

        // Rule 3:
        // After an insert from the active node which is not the root node, we
        // must follow the suffix link and set the active node to the node it
        // points to. If there is no a suffix link, set the active node to the
        // root node. Either way, active edge and active length stay unchanged.
        active_node = tree[active_node].suffix_link;
    }
}

stree::~stree()
{
    delete[] queue;
    delete[] tree;
}

ostream &operator<<(ostream &os, const stree &st)
{
    for (int i = 1; i < st.count; i++)
    {
        stree::node n = st.tree[i];
        os << i << ": [" << n.begin << ", " << n.end
           << ") -> " << n.suffix_link;

        if (n.next.empty())
        {
            os << endl;
            continue;
        }

        os << " = {";

        bool first = true;

        for (auto it : n.next)
        {
            if (first)
            {
                os << " ";
                first = false;
            }
            else
            {
                os << ", ";
            }
            os << it.first << ": " << it.second;
        }

        os << " }" << endl;
    }
    return os;
}
