#include "catch.hpp"
#include "suffix_tree.hpp"

SCENARIO("suffix_trees can be added to", "[suffix_tree]")
{
    suffix_tree tree;

    GIVEN("An empty suffix_tree")
    {
        REQUIRE(tree.size() == 0);

        WHEN("a node is added")
        {
            tree.add('a', 0);

            THEN("the size increments")
            {
                REQUIRE(tree.size() == 1);
            }
            THEN("a child is added")
            {
                REQUIRE(tree.has('a'));
            }
            THEN("the child has the correct value and position")
            {
                suffix_tree* node = tree.get('a');
                REQUIRE(node->value == "a");
                REQUIRE(node->position == 0);
            }
        }
    }

    GIVEN("A non-empty suffix_tree")
    {
        tree.add('a', 0);

        REQUIRE(tree.size() == 1);

        WHEN("a node is appended to")
        {
            tree.get('a')->append('a');

            THEN("letter gets appended to value")
            {
                REQUIRE(tree.get('a')->value == "aa");
            }
        }

        WHEN("a node is added with a unique key")
        {
            tree.add('b', 1);

            THEN("the size increments")
            {
                REQUIRE(tree.size() == 2);
            }
            THEN("a new child is added")
            {
                REQUIRE(tree.has('b'));
            }
            THEN("the child has the correct value and position")
            {
                suffix_tree* node = tree.get('b');
                REQUIRE(node->value == "b");
                REQUIRE(node->position == 1);
            }
        }

        WHEN("a node is added with a non-unique key")
        {
            tree.get('a')->append('a');
            tree.add('a', 2);

            THEN("the size stays the same")
            {
                REQUIRE(tree.size() == 1);
            }
            THEN("a new child is added under existing node with matching key")
            {
                REQUIRE(tree.has('a'));
                REQUIRE(tree.get('a')->has('a'));
            }
            THEN("the child has the correct value and position")
            {
                suffix_tree* node = tree.get('a');
                REQUIRE(node->value == "a");
                REQUIRE(node->position == 2);

                node = node->get('a');
                REQUIRE(node->value == "a");
                REQUIRE(node->position == 0);
            }
        }
    }
}
