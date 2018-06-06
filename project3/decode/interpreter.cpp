#include <fstream>
#include <string>
#include <cinttypes>
#include <bitset>
#include <cmath>
#include "interpreter.hpp"
#include "lookback.hpp"

void interpret(std::string filename) {
    std::ifstream input_file(filename);
    std::ofstream output_file(filename.substr(0, filename.length() - 4));
    char char_buffer;
    uint8_t counter = 0;
    
    // Recover N, L, and S
    input_file.get(char_buffer);
    std::bitset<8> bit_buffer(char_buffer);
    uint8_t N = bit_buffer.to_ulong();

    input_file.get(char_buffer);
    bit_buffer = std::bitset<8>(char_buffer);
    uint8_t L = bit_buffer.to_ulong();

    input_file.get(char_buffer);
    bit_buffer = std::bitset<8>(char_buffer);
    uint8_t S = bit_buffer.to_ulong();

    // Read in a new byte
    input_file.get(char_buffer);
    bit_buffer = std::bitset<8>(char_buffer);

    // Create our lookback buffer
    LookbackBuffer lookback = LookbackBuffer(pow(2, N) - pow(2, L));

    // We can now loop over all of the file's elements.
    while (true) {
        
        // Get the element's length
        std::bitset<4> length = std::bitset<4>();
        uint8_t length_offset = 4 - L;
        for (uint8_t i = 0; i < L; i++) {
            if (counter >= 8) { // We need to read a new byte
                input_file.get(char_buffer);
                bit_buffer = std::bitset<8>(char_buffer);
                counter = 0;
            }
            length.set(3 - (length_offset + i), bit_buffer[7 - counter]);
            ++counter;
        }

        if (length.to_ulong() == 0) { // We want to get string length next

            // Get the string's length
            std::bitset<5> string_length = std::bitset<5>();
            uint8_t strlen_offset = 5 - S;
            for (uint8_t i = 0; i < S; i++) {
                if (counter >= 8) { // We need to read a new byte
                    input_file.get(char_buffer);
                    bit_buffer = std::bitset<8>(char_buffer);
                    counter = 0;
                }
                string_length.set(4 - (strlen_offset + i), bit_buffer[7 - counter]);
                ++counter;
            }

            if (string_length.to_ulong() == 0) { // End-of-file identifier found
                break;
            }
            else { // We want to get the string's characters next
                uint8_t num_chars = string_length.to_ulong();
                std::bitset<8> *output_buffer = new std::bitset<8>();
                for (uint8_t i = 0; i < num_chars; i++) {
                    for (uint8_t j = 0; j < 8; j++) {
                        if (counter >= 8) { // We need to read a new byte
                            input_file.get(char_buffer);
                            bit_buffer = std::bitset<8>(char_buffer);
                            counter = 0;
                        }
                        output_buffer->set(7 - j, bit_buffer[7 - counter]);
                        ++counter;
                    }
                    output_file.write((char*)output_buffer, 1);
                    lookback.add((char*)output_buffer);
                }
            }
        }
        else { // We want to get match offset next
            uint8_t match_length = length.to_ulong() + 1;
            std::bitset<14> offset = std::bitset<14>();
            uint8_t offset_offset = 14 - N;
            for (uint8_t i = 0; i < N; i++) {
                if (counter >= 8) { // We need to read a new byte
                    input_file.get(char_buffer);
                    bit_buffer = std::bitset<8>(char_buffer);
                    counter = 0;
                }
                offset.set(13 - (offset_offset + i), bit_buffer[7 - counter]);
                ++counter;
            }

            // Now we read back from our internal buffer
            for (uint8_t i = 0; i < match_length; i++) {
                char *toAdd = lookback.back(offset.to_ulong());
                output_file.write(toAdd, 1);
                lookback.add(toAdd);
            }
        }
    }
}