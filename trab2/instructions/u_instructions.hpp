#ifndef U_INSTRUCTIONS_HPP
#define U_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>
#include "../riscv_reader.hpp"

using namespace std;

unordered_map<uint32_t, function<int32_t(int32_t)>> initialize_u_instruction_map();

#endif // U_INSTRUCTIONS_HPP
