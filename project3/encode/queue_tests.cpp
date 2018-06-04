#include "catch.hpp"
#include "queue.hpp"

SCENARIO("circular_queue can be pushed to", "[circular_queue]")
{
    GIVEN("three element capacity")
    {
        circular_queue q(3);

        WHEN("nothing is pushed")
        {
            THEN("size is zero")
            {
                REQUIRE(q.length() == 0);
            }

            THEN("pop throws an error")
            {
                REQUIRE_THROWS([&]() {
                    q.pop();
                }());
            }
        }

        WHEN("a value is pushed")
        {
            q.push('a');

            THEN("size is one")
            {
                REQUIRE(q.length() == 1);
            }

            THEN("the next value popped is the same")
            {
                REQUIRE(q.pop() == 'a');
            }
        }

        WHEN("two values are pushed")
        {
            q.push('a');
            q.push('b');

            THEN("size is two")
            {
                REQUIRE(q.length() == 2);
            }

            THEN("the next two values popped are in order")
            {
                REQUIRE(q.pop() == 'a');
                REQUIRE(q.pop() == 'b');
            }
        }

        WHEN("three values are pushed")
        {
            q.push('a');
            q.push('b');
            q.push('c');

            THEN("size is three")
            {
                REQUIRE(q.length() == 3);
            }

            THEN("the next three values popped are in order")
            {
                REQUIRE(q.pop() == 'a');
                REQUIRE(q.pop() == 'b');
                REQUIRE(q.pop() == 'c');
            }

            THEN("additional values cannot be pushed")
            {
                REQUIRE_THROWS([&]() {
                    q.push('d');
                }());

                REQUIRE(q.length() == 3);
            }
        }
    }
}
