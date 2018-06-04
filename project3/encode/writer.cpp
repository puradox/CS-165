#include <fstream>
#include <vector>
#include <tuple>
#include <cinttypes>
#include <bitset>
#include "writer.hpp"
#include "config.hpp"


void write(config conf, std::vector<encode_output> outputs, std::string filename) {
    std::ofstream file(filename);
    std::bitset<3> N(conf.N), L(conf.L), S(conf.S);
    std::bitset<8> *buffer = new std::bitset<8>(N.to_string() + L.to_string() + S.to_string());
    uint8_t counter = 0; // how many bits have been written
    
    // Write N and L to the file as well as the first two bits of S.
    file.write((char*)buffer, 1);

    // Add the last bit of S to the next byte since it didn't fit in the first
    // byte we wrote, and increment the counter.
    buffer->set(counter, S[2]);
    ++counter;

    for (encode_output out : outputs) {
        if (out.length == 0) {
            // Write match length L (which is all zeros in this case)
            for (uint8_t i = 0; i < conf.L; i++) {
                buffer->set(counter, 0);
                ++counter;
                if (counter >= 8) {
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }

            // Write string length S
            std::bitset<5> string_length(out.offset);
            uint8_t strlen_offset = 5 - conf.S;
            for (uint8_t i = 0; i < conf.S; i++) {
                buffer->set(counter, string_length[strlen_offset + i]);
                ++counter;
                if (counter >= 8) {
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }

            // Write the string contents
            for (char c : out.chars) {
                std::bitset<8> char_buffer(c);
                for (uint8_t i = 0; i < 8; i++) {
                    buffer->set(counter, char_buffer[i]);
                    if (counter >= 8) {
                        file.write((char*)buffer, 1);
                        counter = 0;
                    }
                }
            }
        }
        else {
            // Write the match length L
            std::bitset<5> length(out.length);
            uint8_t length_offset = 5 - conf.L;
            for (uint8_t i = 0; i < conf.L; i++) {
                buffer->set(counter, length[length_offset + i]);
                ++counter;
                if (counter >= 8) {
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }

            // Write the match offset N
            std::bitset<14> offset(out.offset);
            uint8_t offset_offset = 14 - conf.N;
            for (uint8_t i = 0; i < conf.N; i++) {
                buffer->set(counter, offset[offset_offset + i]);
                ++counter;
                if (counter >= 8) {
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }
        }
    }

    // Write the end-of-file token.
    for (uint8_t i = 0; i < conf.L + conf.S; i++) {
        buffer->set(counter, 0);
        ++counter;
        if (counter >= 8) {
            file.write((char*)buffer, 1);
            counter = 0;
        }
    }

    // If we have a partial byte left over, we have to write it. We don't care
    // what the remainder of the buffer is filled with since it is after our
    // end-of-file identifier.
    if (counter != 0)
        file.write((char*)buffer, 1);

    delete buffer;
}