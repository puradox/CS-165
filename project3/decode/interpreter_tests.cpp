#include "catch.hpp"
#include "interpreter.hpp"

SCENARIO("interpreter produces correct output", "[interpreter]")
{
    interpret("myOutput.out");
}