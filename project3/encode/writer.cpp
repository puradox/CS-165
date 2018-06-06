#include <fstream>
#include <vector>
#include <cinttypes>
#include <bitset>
#include "writer.hpp"
#include "config.hpp"

void write(config conf, std::vector<encode_output> outputs, std::string filename) {
    std::ofstream file(filename + ".out");
    std::bitset<8> *buffer = new std::bitset<8>();
    uint8_t counter = 0; // how many bits have been written
    
    // Write N, L, and S to the file
    *buffer = std::bitset<8>(conf.N);
    file.write((char*)buffer, 1);
    *buffer = std::bitset<8>(conf.L);
    file.write((char*)buffer, 1);
    *buffer = std::bitset<8>(conf.S);
    file.write((char*)buffer, 1);

    for (encode_output out : outputs) {
        if (out.length == 0) {
            // Write match length L (which is all zeros in this case)
            for (uint8_t i = 0; i < conf.L; i++) {
                buffer->set(7 - counter, 0);
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
                buffer->set(7 - counter, string_length[4 - (strlen_offset + i)]);
                ++counter;
                if (counter >= 8) {
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }

            // Write the string contents
            for (uint8_t i = 0; i < out.chars.length(); i++) {
                std::bitset<8> char_buffer(out.chars.at(i));
                for (uint8_t i = 0; i < 8; i++) {
                    buffer->set(7 - counter, char_buffer[7 - i]);
                    ++counter;
                    if (counter >= 8) {
                        file.write((char*)buffer, 1);
                        counter = 0;
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
                    file.write((char*)buffer, 1);
                    counter = 0;
                }
            }

            // Write the match offset N
            std::bitset<14> offset(out.offset);
            uint8_t offset_offset = 14 - conf.N;
            for (uint8_t i = 0; i < conf.N; i++) {
                buffer->set(7 - counter, offset[13 - (offset_offset + i)]);
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
        buffer->set(7 - counter, 0);
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