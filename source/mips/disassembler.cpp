/**
 * @file disassembler.cpp
 *
 * @brief MIPS Disassembler
 *
 * @author Zac Brannelly (zac.brannelly@gmail.com)
 *
 * SPDX-License-Identifier: GNU General Public License v3.0 only
 */

#include "disassembler.h"
#include <sstream>
#include <stdexcept>
#include "emu_types.h"

std::string format_hex(int32_t value) {
  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << value;
  return ss.str();
}

static const std::string register_table[32] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0",   "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0",   "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8",   "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

std::string format_register(u32 reg) {
  if (reg >= 32) {
    throw std::runtime_error("Invalid register");
  }
  return register_table[reg];
}

std::string disassemble_register(Instruction const &instruction) {
  switch (instruction.full_op) {
  case FULL_OP_ADD:
    return "add " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_ADDU:
    return "addu " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_AND:
    return "and " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_BREAK:
    return "break";
  case FULL_OP_DADD:
    return "dadd " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DADDU:
    return "daddu " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DDIV:
    return "ddiv " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DDIVU:
    return "ddivu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DIV:
    return "div " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DIVU:
    return "divu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DMULT:
    return "dmult " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DMULTU:
    return "dmultu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DSLL:
    return "dsll " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSLL32:
    return "dsll32 " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSLLV:
    return "dsllv " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_DSRA:
    return "dsra " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSRA32:
    return "dsra32 " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSRAV:
    return "dsrav " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_DSRL:
    return "dsrl " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSRL32:
    return "dsrl32 " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_DSRLV:
    return "dsrlv " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_DSUB:
    return "dsub " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_DSUBU:
    return "dsubu " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_JALR:
    return "jalr " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_JR:
    return "jr " + format_register(instruction.reg.rs);
  case FULL_OP_MFHI:
    return "mfhi " + format_register(instruction.reg.rd);
  case FULL_OP_MFLO:
    return "mflo " + format_register(instruction.reg.rd);
  case FULL_OP_MTHI:
    return "mthi " + format_register(instruction.reg.rs);
  case FULL_OP_MTLO:
    return "mtlo " + format_register(instruction.reg.rs);
  case FULL_OP_MULT:
    return "mult " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_MULTU:
    return "multu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_NOR:
    return "nor " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_OR:
    return "or " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_SLL:
    return "sll " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_SLLV:
    return "sllv " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_SLT:
    return "slt " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_SLTU:
    return "sltu " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_SRA:
    return "sra " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_SRAV:
    return "srav " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_SRL:
    return "srl " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           std::to_string(instruction.reg.sa);
  case FULL_OP_SRLV:
    return "srlv " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rt) + ", " +
           format_register(instruction.reg.rs);
  case FULL_OP_SUB:
    return "sub " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_SUBU:
    return "subu " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_SYSCALL:
    return "syscall";
  case FULL_OP_XOR:
    return "xor " + format_register(instruction.reg.rd) + ", " +
           format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TGE:
    return "tge " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TGEU:
    return "tgeu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TLT:
    return "tlt " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TLTU:
    return "tltu " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TEQ:
    return "teq " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  case FULL_OP_TNE:
    return "tne " + format_register(instruction.reg.rs) + ", " +
           format_register(instruction.reg.rt);
  default:
    throw std::runtime_error("Invalid register instruction");
  }
}

std::string disassemble_immediate(Instruction const &instruction) {
  switch (instruction.full_op) {
  case FULL_OP_ADDI:
    return "addi " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_ADDIU:
    return "addiu " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_ANDI:
    return "andi " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BEQ:
    return "beq " + format_register(instruction.immediate.rs) + ", " +
           format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BEQL:
    return "beql " + format_register(instruction.immediate.rs) + ", " +
           format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BGTZ:
    return "bgtz " + format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BGTZL:
    return "bgtzl " + format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BLEZ:
    return "blez " + format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BLEZL:
    return "blezl " + format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BNE:
    return "bne " + format_register(instruction.immediate.rs) + ", " +
           format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_BNEL:
    return "bnel " + format_register(instruction.immediate.rs) + ", " +
           format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_DADDI:
    return "daddi " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_DADDIU:
    return "daddiu " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_LB:
    return "lb " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LBU:
    return "lbu " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LD:
    return "ld " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LDL:
    return "ldl " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LDR:
    return "ldr " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LH:
    return "lh " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LHU:
    return "lhu " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LL:
    return "ll " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LLD:
    return "lld " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LUI:
    return "lui " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_LW:
    return "lw " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LWL:
    return "lwl " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LWR:
    return "lwr " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_LWU:
    return "lwu " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_ORI:
    return "ori " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_SB:
    return "sb " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SC:
    return "sc " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SCD:
    return "scd " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SD:
    return "sd " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SDL:
    return "sdl " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SDR:
    return "sdr " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SH:
    return "sh " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SLTI:
    return "slti " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_SLTIU:
    return "sltiu " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  case FULL_OP_SW:
    return "sw " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SWL:
    return "swl " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_SWR:
    return "swr " + format_register(instruction.immediate.rt) + ", " +
           format_hex(instruction.immediate.immediate) + "(" +
           format_register(instruction.immediate.rs) + ")";
  case FULL_OP_XORI:
    return "xori " + format_register(instruction.immediate.rt) + ", " +
           format_register(instruction.immediate.rs) + ", " +
           format_hex(instruction.immediate.immediate);
  default:
    throw std::runtime_error("Invalid immediate instruction");
  }
}

std::string disassemble_jump(Instruction const &instruction) {
  switch (instruction.full_op) {
  case FULL_OP_J:
    return "j " + format_hex(instruction.jump.target);
  case FULL_OP_JAL:
    return "jal " + format_hex(instruction.jump.target);
  default:
    throw std::runtime_error("Invalid jump instruction");
  }
}

std::string disassemble_register_immediate(Instruction const &instruction) {
  switch (instruction.full_op) {
  case FULL_OP_BLTZ:
    return "bltz " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BGEZ:
    return "bgez " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BLTZL:
    return "bltzl " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BGEZL:
    return "bgezl " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TGEI:
    return "tgei " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TGEIU:
    return "tgeiu " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TLTI:
    return "tlti " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TLTIU:
    return "tltiu " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TEQI:
    return "teqi " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_TNEI:
    return "tnei " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BLTZAL:
    return "bltzal " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BGEZAL:
    return "bgezal " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BLTZALL:
    return "bltzall " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  case FULL_OP_BGEZALL:
    return "bgezall " + format_register(instruction.regimm.rs) + ", " +
           format_hex(instruction.regimm.immediate);
  default:
    throw std::runtime_error("Invalid register immediate instruction");
  }
}

std::string disassemble_get_fpu_format(Instruction const &instruction) {
  switch (instruction.coprocessor.cop_fpu.fmt) {
  case FMT_SINGLE:
    return "s";
  case FMT_DOUBLE:
    return "d";
  case FMT_WORD:
    return "w";
  case FMT_LONG:
    return "l";
  default:
    throw std::runtime_error("Invalid FPU format");
  }
}

std::string disassemble_coprocessor(Instruction const &instruction) {
  switch (instruction.full_op) {
  // FPU instructions
  case FULL_OP_FADD:
    return "add." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.ft);
  case FULL_OP_FABS:
    return "abs." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CF:
    return "C.F." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.ft);
  case FULL_OP_CEILL:
    return "ceil.l." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CEILW:
    return "ceil.w." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CVTD:
    return "cvt.d." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CVTL:
    return "cvt.l." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CVTS:
    return "cvt.s." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_CVTW:
    return "cvt.w." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FDIV:
    return "div." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.ft);
  case FULL_OP_FLOORL:
    return "floor.l." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FLOORW:
    return "floor.w." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FMOV:
    return "mov." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FMUL:
    return "mul." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.ft);
  case FULL_OP_FNEG:
    return "neg." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_ROUNDL:
    return "round.l." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_ROUNDW:
    return "round.w." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FSQRT:
    return "sqrt." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_FSUB:
    return "sub." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.ft);
  case FULL_OP_TRUNCL:
    return "trunc.l." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);
  case FULL_OP_TRUNCW:
    return "trunc.w." + disassemble_get_fpu_format(instruction) + " $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" +
           std::to_string(instruction.coprocessor.cop_fpu.fs);

  // Coprocessor instructions
  case FULL_OP_TLBR:
    return "tlbr";
  case FULL_OP_TLBWI:
    return "tlbwi";
  case FULL_OP_TLBWR:
    return "tlbwr";
  case FULL_OP_TLBP:
    return "tlbp";
  case FULL_OP_ERET:
    return "eret";
  case FULL_OP_MTC0:
    return "mtc0 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_MFC0:
    return "mfc0 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_DMTC0:
    return "dmfc0 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_DMFC0:
    return "dmfc0 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_CFC0:
    return "cfc0 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_CFC1:
    return "cfc1 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);
  case FULL_OP_CFC2:
    return "cfc2 " +
           format_register(instruction.coprocessor.cop_op_register.rt) + ", $" +
           std::to_string(instruction.coprocessor.cop_op_register.rd);

  case FULL_OP_BC0F:
    return "bc0f " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC1F:
    return "bc1f " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC2F:
    return "bc2f " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);

  case FULL_OP_BC0T:
    return "bc0t " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC1T:
    return "bc1t " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC2T:
    return "bc2t " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);

  case FULL_OP_BC0FL:
    return "bc0fl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC1FL:
    return "bc1fl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC2FL:
    return "bc2fl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);

  case FULL_OP_BC0TL:
    return "bc0tl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC1TL:
    return "bc1tl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);
  case FULL_OP_BC2TL:
    return "bc2tl " +
           format_hex(instruction.coprocessor.cop_op_no_register.immediate);

  // TODO: Handle these properly.
  case FULL_OP_COP0:
    return "cop0";
  case FULL_OP_COP1:
    return "cop1";
  case FULL_OP_COP2:
    return "cop2";

  default:
    throw std::runtime_error("Invalid FPU instruction");
  }
}

std::string disassemble_cache(Instruction const &instruction) {
  if (instruction.full_op < FULL_OP_CACHE_INDEX_INVALIDATE ||
      instruction.full_op > FULL_OP_CACHE_HIT_WRITE_BACK_DATA_CACHE) {
    throw std::runtime_error("Invalid cache instruction");
  }
  return "cache " + std::to_string(instruction.cache.cache_op) + ", " +
         format_hex(instruction.cache.offset) + "(" +
         format_register(instruction.cache.base) + ")";
}

std::string disassemble(Instruction const &instruction) {
  switch (instruction.type) {
  case TYPE_REGISTER:
    return disassemble_register(instruction);
  case TYPE_IMMEDIATE:
    return disassemble_immediate(instruction);
  case TYPE_JUMP:
    return disassemble_jump(instruction);
  case TYPE_REGISTER_IMMEDIATE:
    return disassemble_register_immediate(instruction);
  case TYPE_COPROCESSOR:
    return disassemble_coprocessor(instruction);
  case TYPE_CACHE:
    return disassemble_cache(instruction);
  case TYPE_NOOP:
    return "nop";
  default:
    throw std::runtime_error("Invalid instruction type");
  }
}
