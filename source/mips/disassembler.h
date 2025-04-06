/**
 * @file disassembler.h
 *
 * @brief MIPS Disassembler
 *
 * @author Zac Brannelly (zac.brannelly@gmail.com)
 *
 * SPDX-License-Identifier: GNU General Public License v3.0 only
 */

#pragma once

#include "decoder.h"
#include <string>

std::string disassemble_binary(u32 *binary, size_t size);
std::string disassemble(u32 const &instruction);
std::string disassemble(Instruction const &instruction);
