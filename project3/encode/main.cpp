#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <iomanip>

#include "config.hpp"
#include "stree.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        config::usage();
        return 1;
    }

    config c;

    for (int i = 1; i < argc - 1; i++)
        if (c.parse(argv[i]) != 0)
            return 22; // Invalid argument

    std::ifstream is(argv[argc - 1], std::ifstream::binary);

    stree st(c);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    //
    // Begin timing
    //

    char letter;
    int need_to_push = pow(2, c.L);

    while (is)
    {
        // Add to lookahead
        while (need_to_push > 0)
        {
            is.read(&letter, 1);
            st.push(letter);
            need_to_push--;
        }

        // Consume input until generating an output
        bool generated_output = false;
        while (!generated_output)
        {
            generated_output = st.pop();
            need_to_push++;
        }
    }

    // Ensure that the suffix tree has output the last item.
    st.flush();

    // Write to stderr
    write(c, st.count, st.get_output());

    //
    // End timing
    //
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cerr << "Compressing files took a total of " << std::setprecision(10) << time_span.count() << " seconds." << std::endl;

    return 0;
}
