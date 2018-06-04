#include <string>
#include <cinttypes>
#include <cassert>
#include <ostream>
#include "suffix_tree.hpp"

suffix_tree::~suffix_tree()
{
    for (int i = 0; i < 256; i++)
        if (this->children[i] != nullptr)
            delete this->children[i];
}

bool suffix_tree::has(char key)
{
    return this->get(key) != nullptr;
}

suffix_tree *suffix_tree::get(char key)
{
    return this->children[(uint8_t)key];
}

void suffix_tree::append(char key)
{
    assert(this->parent != nullptr);
    assert(this->value != "");

    if (this->count == 0) // no children
    {
        this->value.append(1, key);
    }
    else if (this->has(key))
    {

    }

}

suffix_tree *suffix_tree::add(char key, uint16_t position)
{
    if (this->has(key)) // non-unique key
    {
        // Keep a reference to the original node so we don't lose it
        suffix_tree *original = this->get(key);
        assert(original->value.length() > 1);

        // Replace the orignal node with a new node
        suffix_tree *added = new suffix_tree(this, key, position);
        this->children[(uint8_t)key] = added;

        // Add the original node as a child of the new node
        original->value = original->value.substr(1); // cut off the expanded letter
        added->add(original);
        original->parent = added;
    }
    else // unique key
    {
        this->children[(uint8_t)key] = new suffix_tree(this, key, position);
        this->count++;
    }

    return this->get(key);
}

void suffix_tree::add(suffix_tree* node)
{
    assert(this->get(node->value.at(0)) == nullptr);

    this->children[(uint8_t)node->value.at(0)] = node;
    this->count++;
}

uint16_t suffix_tree::size()
{
    return this->count;
}

std::ostream & operator<< (std::ostream &out, suffix_tree const &t)
{
    if (t.parent == nullptr)
        out << "(root)";
    else
        out << "(" << t.value << ", " << t.position << ")";

    bool hasChildren = false;

    for (int i = 0; i < 256; i++)
    {
        if (t.children[i] != nullptr)
        {
            if (!hasChildren)
            {
                out << " ->";
                hasChildren = true;
            }

            out << " (" << t.children[i]->value << ", " << t.children[i]->position << ")";
        }
    }

    return out;
}
