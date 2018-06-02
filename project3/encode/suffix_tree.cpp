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
    return this->children[key] != nullptr;
}

void suffix_tree::append(char key)
{
    assert(this->parent != nullptr);
    assert(this->value != "");

    this->value.append(1, key);
}

suffix_tree *suffix_tree::add(char key, uint16_t position)
{
    assert(this->children[key] == nullptr);

    this->children[key] = new suffix_tree(this, std::string(1, key), position);
    this->count++;
    return this->children[key];
}

suffix_tree *suffix_tree::expand(char key, uint16_t position)
{
    assert(this->parent != nullptr);
    assert(this->value != "");
    assert(this->value.length() > 0);

    // Move the current node down to its children and append to its value
    this->value.append(1, key);
    suffix_tree *result = new suffix_tree(this, this->value.substr(1), this->position);
    this->children[this->value.at(1)] = result;

    // Update this node's value and position to represent the new node.
    this->value = this->value.at(0);
    this->position = position;

    return result;
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
