#include "catch.hpp"
#include "config.hpp"
#include "stree.hpp"
#include <iostream>

#define REQUIRE_NODE(node, b, e) \
    REQUIRE(node.begin == b); \
    REQUIRE(node.end == e);

#define REQUIRE_SUFF(node, b, e, s) \
    REQUIRE(node.begin == b); \
    REQUIRE(node.end == e); \
    REQUIRE(node.suffix_link == s);

SCENARIO("stree can be added to", "[stree]")
{
    GIVEN("Example 'abcabxabcd'")
    {
        stree stree(config{9, 3, 1});
        stree.push("abcabxabcd");

        INFO("Capacity: " << stree.capacity);
        INFO("Longest match length: " << stree.longest_match_length);
        INFO("Longest literal length: " << stree.longest_literal_length);

        WHEN("'abc' is inserted")
        {
            for (int i = 0; i < 3; i++)
                stree.pop();

            INFO(stree);

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

            INFO(stree);

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

            INFO(stree);

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 9);
            }

            THEN("nodes have correct begin and end")
            {
                REQUIRE_NODE(stree[1], 2, 0);
                REQUIRE_NODE(stree[2], 2, 0);
                REQUIRE_NODE(stree[3], 2, 0);
                REQUIRE_SUFF(stree[4], 3, 5, 6);
                REQUIRE_NODE(stree[5], 5, 0);
                REQUIRE_NODE(stree[6], 4, 5);
                REQUIRE_NODE(stree[7], 5, 0);
                REQUIRE_NODE(stree[8], 5, 0);
            }
        }

        WHEN("'abcabxabc' is inserted")
        {
            for (int i = 0; i < 9; i++)
                stree.pop();

            INFO(stree);

            THEN("correct amount of nodes")
            {
                REQUIRE(stree.count == 9);
            }

            THEN("nodes have correct begin and end")
            {
                REQUIRE_NODE(stree[1], 2, 0);
                REQUIRE_NODE(stree[2], 2, 0);
                REQUIRE_NODE(stree[3], 2, 0);
                REQUIRE_SUFF(stree[4], 3, 5, 6);
                REQUIRE_NODE(stree[5], 5, 0);
                REQUIRE_NODE(stree[6], 4, 5);
                REQUIRE_NODE(stree[7], 5, 0);
                REQUIRE_NODE(stree[8], 5, 0);
            }
        }

        WHEN("'abcabxabcd' is inserted")
        {
            for (int i = 0; i < 10; i++)
                stree.pop();

            INFO(stree);

            THEN("correct amount of nodes")
            {
                for (auto output : stree.get_output())
                    std::cout << output << std::endl;
                REQUIRE(stree.count == 16);
            }

            THEN("nodes have correct begin and end")
            {
                REQUIRE_NODE( stree[1], 3, 0);
                REQUIRE_NODE( stree[2], 3, 0);
                REQUIRE_NODE( stree[3], 3, 0);
                REQUIRE_SUFF( stree[4], 3, 5, 6);
                REQUIRE_NODE( stree[5], 5, 0);
                REQUIRE_NODE( stree[6], 4, 5);
                REQUIRE_NODE( stree[7], 5, 0);
                REQUIRE_NODE( stree[8], 5, 0);
                REQUIRE_SUFF( stree[9], 8, 9, 11);
                REQUIRE_NODE(stree[10], 9, 0);
                REQUIRE_SUFF(stree[11], 8, 9, 13);
                REQUIRE_NODE(stree[12], 9, 0);
                REQUIRE_NODE(stree[13], 8, 9);
                REQUIRE_NODE(stree[14], 9, 0);
                REQUIRE_NODE(stree[15], 9, 0);
            }
        }
    }
}
