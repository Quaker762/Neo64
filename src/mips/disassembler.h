#pragma once
#include <string>
#include "decoder.h"

std::string disassemble_binary(uint32_t* binary, size_t size);
std::string disassemble(uint32_t const& instruction);
std::string disassemble(Instruction const& instruction);
