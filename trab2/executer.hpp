#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <cstdint>
#include <unordered_map>
#include <functional>
#include "instructions/b_instructions.hpp"
#include "instructions/i_instructions.hpp"
#include "instructions/j_instructions.hpp"
#include "instructions/r_instructions.hpp"
#include "instructions/s_instructions.hpp"
#include "instructions/u_instructions.hpp"

void execute(char instruction_format);
void initialize_instruction_maps();

#endif // EXECUTER_HPP
