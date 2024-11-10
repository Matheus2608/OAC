#ifndef S_INSTRUCTIONS_HPP
#define S_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>
#include "../memory.hpp"

using namespace std;

unordered_map<uint32_t, function<void(int32_t, int32_t, int32_t)>> initialize_s_instruction_map();

#endif // S_INSTRUCTIONS_HPP
