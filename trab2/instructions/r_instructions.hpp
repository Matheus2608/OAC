#ifndef R_INSTRUCTIONS_HPP
#define R_INSTRUCTIONS_HPP

#include <unordered_map>
#include <functional>
#include <cstdint>

using namespace std;

unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> initialize_r_instruction_map();

#endif // R_INSTRUCTIONS_HPP
