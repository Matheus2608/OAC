#ifndef I_INSTRUCTIONS_HPP
#define I_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../riscv_reader.hpp"

using namespace std;

std::unordered_map<uint32_t, std::function<int32_t(int32_t, int32_t)>> initialize_i_instruction_map();

#endif // B_INSTRUCTIONS_HPP
