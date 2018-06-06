#include "catch.hpp"
#include "stree.hpp"
#include <iostream>

#define REQUIRE_NODE(node, b, e) {\
    REQUIRE(node.begin == b); \
    REQUIRE(node.end == e); }

SCENARIO("stree can be added to", "[stree]")
{
    GIVEN("Example 'abcabxabcd'")
    {
        stree stree(10);
        stree.push("abcabxabcd");

        WHEN("'abc' is inserted")
        {
            for (int i = 0; i < 3; i++)
                stree.pop();

            std::cout << stree << std::endl;

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 4);
            }

            THEN("nodes have correct begin and end")
            {
                REQUIRE_NODE(stree[1], 0, 0);
                REQUIRE_NODE(stree[2], 1, 0);
                REQUIRE_NODE(stree[3], 2, 0);
            }
        }

        WHEN("'abcab' is inserted")
        {
            for (int i = 0; i < 5; i++)
                stree.pop();

            std::cout << stree << std::endl;

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 4);
            }

            THEN("nodes have correct begin and end")
            {
                REQUIRE_NODE(stree[1], 0, 0);
                REQUIRE_NODE(stree[2], 1, 0);
                REQUIRE_NODE(stree[3], 2, 0);
            }
        }

        WHEN("'abcabx' is inserted")
        {
            for (int i = 0; i < 6; i++)
                stree.pop();

            std::cout << stree << std::endl;

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 10);
            }
        }

        WHEN("'abcabxabc' is inserted")
        {
            for (int i = 0; i < 9; i++)
                stree.pop();

            std::cout << stree << std::endl;

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 10);
            }
        }

        WHEN("'abcabxabcd' is inserted")
        {
            for (int i = 0; i < 10; i++)
                stree.pop();

            std::cout << stree << std::endl;

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 16);
            }
        }
    }
}
