#ifndef B_INSTRUCTIONS_HPP
#define B_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../riscv_reader.hpp"

using namespace std;

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_b_instruction_map();

#endif // B_INSTRUCTIONS_HPP
