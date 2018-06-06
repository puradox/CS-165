#include <iostream>
#include <iomanip>
#include <vector>
#include <cinttypes>
#include <bitset>
#include "writer.hpp"
#include "config.hpp"

void write(config conf, uint64_t inChars, std::vector<encode_output> outputs) {
    std::bitset<8> *buffer = new std::bitset<8>();
    uint64_t outChars = 0;
    uint8_t  counter  = 0; // how many bits have been written

    // Write N, L, and S to standard output
    *buffer = std::bitset<8>(conf.N);
    std::cout << (char*)buffer;
    ++outChars;
    *buffer = std::bitset<8>(conf.L);
    std::cout << (char*)buffer;
    ++outChars;
    *buffer = std::bitset<8>(conf.S);
    std::cout << (char*)buffer;
    ++outChars;

    for (encode_output out : outputs) {
        if (out.length == 0) {
            // Write match length L (which is all zeros in this case)
            for (uint8_t i = 0; i < conf.L; i++) {
                buffer->set(7 - counter, 0);
                ++counter;
                if (counter >= 8) {
                    std::cout << (char*)buffer;
                    counter = 0;
                    ++outChars;
                }
            }

            // Write string length S
            std::bitset<5> string_length(out.offset);
            uint8_t strlen_offset = 5 - conf.S;
            for (uint8_t i = 0; i < conf.S; i++) {
                buffer->set(7 - counter, string_length[4 - (strlen_offset + i)]);
                ++counter;
                if (counter >= 8) {
                    std::cout << (char*)buffer;
                    counter = 0;
                    ++outChars;
                }
            }

            // Write the string contents
            for (uint8_t i = 0; i < out.chars.length(); i++) {
                std::bitset<8> char_buffer(out.chars.at(i));
                for (uint8_t i = 0; i < 8; i++) {
                    buffer->set(7 - counter, char_buffer[7 - i]);
                    ++counter;
                    if (counter >= 8) {
                        std::cout << (char*)buffer;
                        counter = 0;
                        ++outChars;
                    }
                }
            }
        }
        else {
            // Write the match length L
            std::bitset<4> length(out.length - 1);
            uint8_t length_offset = 4 - conf.L;
            for (uint8_t i = 0; i < conf.L; i++) {
                buffer->set(7 - counter, length[3 - (length_offset + i)]);
                ++counter;
                if (counter >= 8) {
                    std::cout << (char*)buffer;
                    counter = 0;
                    ++outChars;
                }
            }

            // Write the match offset N
            std::bitset<14> offset(out.offset);
            uint8_t offset_offset = 14 - conf.N;
            for (uint8_t i = 0; i < conf.N; i++) {
                buffer->set(7 - counter, offset[13 - (offset_offset + i)]);
                ++counter;
                if (counter >= 8) {
                    std::cout << (char*)buffer;
                    counter = 0;
                    ++outChars;
                }
            }
        }
    }

    // Write the end-of-file token.
    for (uint8_t i = 0; i < conf.L + conf.S; i++) {
        buffer->set(7 - counter, 0);
        ++counter;
        if (counter >= 8) {
            std::cout << (char*)buffer;
            counter = 0;
            ++outChars;
        }
    }

    // If we have a partial byte left over, we have to write it. We don't care
    // what the remainder of the buffer is filled with since it is after our
    // end-of-file identifier.
    if (counter != 0) {
        std::cout << (char*)buffer;
        ++outChars;
    }

    double compressedGain = 100 - (100 * ((double)outChars/inChars));

    std::cerr << "Parameter Values:" << std::endl;
    std::cerr << "N=" << (int)conf.N << ", L=" << (int)conf.L << ", S=" << (int)conf.S << std::endl;
    std::cerr << "Bytes in: " << inChars << ", Bytes out: " << outChars << std::endl;
    std::cerr << "Compressed file was " << std::setprecision(3) << compressedGain << "% smaller than original." << std::endl;

    delete buffer;
}

std::ostream &operator<<(std::ostream &os, const encode_output &eo)
{
    if (eo.length == 0)
    {
        // string literal
        return os << eo.chars;
    }
    else
    {
        // match
        return os << "(len=" << eo.length << ", offset=" << eo.offset << ")";
    }
}
