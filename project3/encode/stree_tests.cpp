#include "catch.hpp"
#include "config.hpp"
#include "stree.hpp"
#include "writer.hpp"
#include <iostream>
#include <vector>

#define REQUIRE_NODE(node, b, e) \
    REQUIRE(node.begin == b); \
    REQUIRE(node.end == e);

#define REQUIRE_SUFF(node, b, e, s) \
    REQUIRE(node.begin == b); \
    REQUIRE(node.end == e); \
    REQUIRE(node.suffix_link == s);

#define REQUIRE_MATCH(out, len, off) \
    REQUIRE(out.length == len); \
    REQUIRE(out.offset == off);

#define REQUIRE_LTRAL(out, len, letters) \
    REQUIRE(out.length == 0); \
    REQUIRE(out.offset == len); \
    REQUIRE(out.chars == letters);

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

SCENARIO("stree can be added to", "[stree]")
{
    GIVEN("Example 'abcabxabcd'")
    {
        stree stree(config{9, 3, 1});
        stree.push("abcabxabcd");

        INFO("Capacity: " << stree.capacity);
        INFO("Longest match length: " << stree.max_match_length);
        INFO("Longest literal length: " << stree.max_literal_length);

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

SCENARIO("stree can be flushed", "[stree]")
{
    GIVEN("Example 'abcabxabcd'") {
        stree stree(config{9, 3, 0});
        stree.push("abcabxabcd");

        INFO("Capacity: " << stree.capacity);
        INFO("Longest match length: " << stree.max_match_length);
        INFO("Longest literal length: " << stree.max_literal_length);

        WHEN("'abc' is inserted")
        {
            for (int i = 0; i < 3; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("output is valid")
            {
                std::vector<encode_output> outs = stree.get_output();
                REQUIRE(outs.size() == 3);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
            }
        }

        WHEN("'abc' is inserted and tree is flushed")
        {
            for (int i = 0; i < 3; i++)
                stree.pop();

            stree.flush();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("output is unchanged")
            {
                std::vector<encode_output> outs = stree.get_output();
                REQUIRE(outs.size() == 3);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
            }
        }

        WHEN("'abca' is inserted")
        {
            for (int i = 0; i < 4; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("output is valid")
            {
                REQUIRE(outs.size() == 3);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
            }
        }

        WHEN("'abca' is inserted and tree is flushed")
        {
            for (int i = 0; i < 4; i++)
                stree.pop();

            stree.flush();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("there is an additional output for last 'a'")
            {
                REQUIRE(outs.size() == 4);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_LTRAL(outs.at(3), 1, "a");
            }
        }

        WHEN("'abcab' is inserted")
        {
            for (int i = 0; i < 4; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("output is valid")
            {
                REQUIRE(outs.size() == 3);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
            }
        }

        WHEN("'abcab' is inserted and tree is flushed")
        {
            for (int i = 0; i < 5; i++)
                stree.pop();

            stree.flush();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("there is an additional output for last 'ab'")
            {
                REQUIRE(outs.size() == 4);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_MATCH(outs.at(3), 2, 3);
            }
        }

        WHEN("'abcabxabc' is inserted and tree is flushed")
        {
            for (int i = 0; i < 9; i++)
                stree.pop();

            stree.flush();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("there is an additional output for last 'abc'")
            {
                REQUIRE(outs.size() == 6);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_MATCH(outs.at(3), 2, 3);
                REQUIRE_LTRAL(outs.at(4), 1, "x");
                REQUIRE_MATCH(outs.at(5), 3, 6);
            }
        }

        WHEN("'abcabxabcd' is inserted")
        {
            for (int i = 0; i < 10; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();
            INFO(outs);

            THEN("output is valid")
            {
                REQUIRE(outs.size() == 7);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_MATCH(outs.at(3), 2, 3);
                REQUIRE_LTRAL(outs.at(4), 1, "x");
                REQUIRE_MATCH(outs.at(5), 3, 6);
                REQUIRE_LTRAL(outs.at(6), 1, "d");
            }
        }

    }
}

SCENARIO("stree with a small sliding window", "[stree]")
{
    GIVEN("Example 'abcdabcabc'")
    {
        stree stree(config{2, 3, 0});

        INFO("Capacity: " << stree.capacity);
        INFO("Max match length: " << stree.max_match_length);
        INFO("Max literal length: " << stree.max_literal_length);

        WHEN("'abcd' has been inserted")
        {
            stree.push("abcd");
            for (int i = 0; i < 4; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();

            INFO(stree);
            INFO(outs);

            THEN("nodes are valid")
            {
                REQUIRE(stree.count == 5);
                REQUIRE_NODE(stree[1], 0, 0);
                REQUIRE_NODE(stree[2], 1, 0);
                REQUIRE_NODE(stree[3], 2, 0);
                REQUIRE_NODE(stree[4], 3, 0);
            }

            THEN("outputs are valid")
            {
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_LTRAL(outs.at(3), 1, "d");
            }
        }

        WHEN("'abcdabc' has been inserted")
        {
            stree.push("abcd");
            for (int i = 0; i < 4; i++)
                stree.pop();

            stree.push("abc");
            for (int i = 0; i < 3; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();

            INFO(stree);
            INFO(outs);

            THEN("outputs are valid")
            {
                REQUIRE(outs.size() == 7);
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_LTRAL(outs.at(3), 1, "d");
                REQUIRE_LTRAL(outs.at(4), 1, "a");
                REQUIRE_LTRAL(outs.at(5), 1, "b");
                REQUIRE_LTRAL(outs.at(6), 1, "c");
            }
        }

        WHEN("'abcdabcabc' has been inserted")
        {
            stree.push("abcd");
            for (int i = 0; i < 4; i++)
                stree.pop();

            stree.push("abc");
            for (int i = 0; i < 3; i++)
                stree.pop();

            stree.push("abc");
            for (int i = 0; i < 3; i++)
                stree.pop();

            std::vector<encode_output> outs = stree.get_output();

            INFO(stree);
            INFO(outs);

            THEN("outputs are valid")
            {
                REQUIRE_LTRAL(outs.at(0), 1, "a");
                REQUIRE_LTRAL(outs.at(1), 1, "b");
                REQUIRE_LTRAL(outs.at(2), 1, "c");
                REQUIRE_LTRAL(outs.at(3), 1, "d");
                REQUIRE_LTRAL(outs.at(4), 1, "a");
                REQUIRE_LTRAL(outs.at(5), 1, "b");
                REQUIRE_LTRAL(outs.at(6), 1, "c");
                REQUIRE_LTRAL(outs.at(7), 1, "a");
                REQUIRE_LTRAL(outs.at(8), 1, "b");
                REQUIRE_LTRAL(outs.at(9), 1, "c");
            }
        }
    }
}
