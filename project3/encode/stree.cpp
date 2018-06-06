#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cinttypes>
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
    if (has(key))
        throw "already exists!";

    next.insert({key, node});
}

void stree::node::set(char key, int node)
{
    next.at(key) = node;
}

void stree::node::remove(char key)
{
    next.erase(key);
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
    if (queue[head].parent != -1)
        tree[queue[head].parent].remove(queue[head].letter);

    // Add the new value to the queue
    queue[head].letter = letter;
    queue[head].parent = -1;
    head = (head + 1) % capacity;
    size++;
}

void stree::push(string letters)
{
    for (char letter : letters)
        push(letter);
}

int stree::new_node(int start, int end)
{
    int last_added = count++ % (2 * capacity);
    tree[last_added] = node(start, end);
    return last_added;
}

char stree::active_letter()
{
    return queue[active_edge].letter;
}

void stree::link(int node)
{
    if (needs_link)
        tree[needs_link].suffix_link = node;
    needs_link = node;
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

bool stree::pop()
{
    //
    // Pop from the circular queue
    //

    // Check for underflow
    if (size == 0)
        throw underflow_error("stree::pop underflow");

    // Process the current character in the queue
    int pos = tail;
    char letter = queue[tail].letter;
    tail = (tail + 1) % capacity;
    size--;

    //
    // Update the suffix tree
    //

    bool has_outputted = false;

    needs_link = 0;
    letters_processed++;
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
            if (queue[tree[next].begin + active_length].letter == letter &&
                remainder <= max_match_length)
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

            int split = new_node(pos - active_length, pos);
            tree[active_node].set(active_letter(), split);
            queue[pos - active_length].parent = active_node;

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

            if (!has_outputted)
            {
                output();
                has_outputted = true;
            }
        }
        else
        {
            // Otherwise, there is no edge with the matching letter
            int leaf = new_node(pos);
            tree[active_node].add(letter, leaf);
            queue[pos].parent = active_node;
            link(active_node); // See Rule 2 above

            output();
            has_outputted = true;
        }

        remainder--;

        if (active_node == ROOT && active_length > 0)
        {
            // Rule 1:
            // If after an insertion from the active node = root and the active
            // length is greater than 0, then:
            //   1. active node is not changed
            //   2. active length is decremented
            //   3. active edge is shifted right (to the first character of the
            //      next suffix we must insert)
            active_length--;
            active_edge = pos - remainder + 1;
        }
        else
        {
            // Rule 3:
            // After an insert from the active node which is not the root node,
            // we must follow the suffix link and set the active node to the
            // node it points to. If there is no a suffix link, set the active
            // node to the root node. Either way, active edge and active length
            // stay unchanged.
            active_node = tree[active_node].suffix_link;
        }
    }

    return has_outputted;
}

// Almost identitical to stree::output, but +1 to the match length.
void stree::flush()
{
    int pos = tail - 1;
    if (pos < 0)
        pos += capacity;

    if (remainder < 0)
        throw "remainder negative?!";
    else if (remainder == 1)
        return;
    else if (remainder == 2)
        outputs.push_back(encode_output{0, 1, string(1, queue[pos].letter)});
    else
    {
        int offset = tail - remainder;
        if (offset < 0)
            offset += capacity; // circular queue wrapping behavior

        outputs.push_back(encode_output{
            (uint16_t)remainder,
            (uint16_t)offset,
            ""});
    }
}

void stree::output()
{
    int pos = tail - 1;
    if (pos < 0)
        pos += capacity;

    // Produce an encode_output and push it to outputs
    if (remainder < 0)
        throw "remainder negative?!";
    else if (remainder == 0)
        return;
    else if (remainder == 1)
        outputs.push_back(encode_output{0, 1, string(1, queue[pos].letter)});
    else
    {
        int offset = tail - remainder;
        if (offset < 0)
            offset += capacity; // circular queue wrapping behavior

        outputs.push_back(encode_output{
            (uint16_t)(remainder - 1),
            (uint16_t)offset,
            ""});
    }
}

vector<encode_output> stree::get_output()
{
    vector<encode_output> result;
    vector<encode_output> literals;

    for (auto out : outputs)
    {
        if (out.length == 0)
        {
            // literal character
            if (literals.size() >= (unsigned long)max_literal_length)
            {
                string letters = "";
                for (auto literal : literals)
                    letters.append(literal.chars);

                result.push_back(encode_output{0, (uint16_t)literals.size(), letters});
                literals.clear();
            }

            literals.push_back(out);
        }
        else
        {
            if (literals.size() > 0)
            {
                string letters;
                for (auto literal : literals)
                    letters.append(literal.chars);

                result.push_back(encode_output{0, (uint16_t)literals.size(), letters});
                literals.clear();
            }

            result.push_back(out);
        }
    }

    if (literals.size() > 0)
    {
        string letters;
        for (auto literal : literals)
            letters.append(literal.chars);

        result.push_back(encode_output{0, (uint16_t)literals.size(), letters});
        literals.clear();
    }

    return result;
}

stree::~stree()
{
    delete[] queue;
    delete[] tree;
}

ostream &operator<<(ostream &os, const stree &st)
{
    for (int i = 1; i < (2 * st.capacity) && i < st.count; i++)
    {
        stree::node n = st.tree[i];
        string letters = "";
        int end = n.end == 0 ? st.tail : n.end;
        for (int j = n.begin; j < end; j++)
            letters.append(1, st.queue[j].letter);

        os << i << ": " << letters << " [" << n.begin << ", " << n.end
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
