#include <cstdint>
#include <unordered_map>
#include <functional>

using namespace std;

unordered_map<uint32_t, function<int32_t(int32_t, int32_t)>> r_format_instruction_map;
// r_format_instruction_map[0b0110011] = add;

int32_t add(int32_t reg1, int32_t reg2) {
    return reg1 + reg2;
}

int32_t sub(int32_t reg1, int32_t reg2) {
    return reg1 - reg2;
}

int32_t sub(int32_t reg1, int32_t reg2) {
    return reg1 - reg2;
}

int32_t sll(int32_t reg1, int32_t reg2) {
    return reg1 << reg2;
}

int32_t _and(int32_t reg1, int32_t reg2) {
    return reg1 & reg2;
}

int32_t _or(int32_t reg1, int32_t reg2) {
    return reg1 | reg2;
}

int32_t _xor(int32_t reg1, int32_t reg2) {
    return reg1 ^ reg2;
}
