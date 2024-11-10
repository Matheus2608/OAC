#ifndef J_INSTRUCTIONS_HPP
#define J_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>
#include "../riscv_reader.hpp"

using namespace std;

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_j_instruction_map();

#endif // J_INSTRUCTIONS_HPP
