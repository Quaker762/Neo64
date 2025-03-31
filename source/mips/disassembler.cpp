#include "disassembler.h"
#include <stdexcept>
#include <sstream>

std::string format_hex(int32_t value) {
  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << value;
  return ss.str();
}

std::string disassemble_register(Instruction const& instruction) {
  switch (instruction.full_op) {
    case FULL_OP_ADD:
      return "add $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_ADDU:
      return "addu $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_AND:
      return "and $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_BREAK:
      return "break";
    case FULL_OP_DADD:
      return "dadd $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DADDU:
      return "daddu $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DDIV:
      return "ddiv $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DDIVU:
      return "ddivu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DIV:
      return "div $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DIVU:
      return "divu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DMULT:
      return "dmult $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DMULTU:
      return "dmultu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DSLL:
      return "dsll $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSLL32:
      return "dsll32 $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSLLV:
      return "dsllv $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_DSRA:
      return "dsra $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSRA32:
      return "dsra32 $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSRAV:
      return "dsrav $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_DSRL:
      return "dsrl $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSRL32:
      return "dsrl32 $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_DSRLV:
      return "dsrlv $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_DSUB:
      return "dsub $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_DSUBU:
      return "dsubu $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_JALR:
      return "jalr $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_JR:
      return "jr $" + std::to_string(instruction.reg.rs);
    case FULL_OP_MFHI:
      return "mfhi $" + std::to_string(instruction.reg.rd);
    case FULL_OP_MFLO:
      return "mflo $" + std::to_string(instruction.reg.rd);
    case FULL_OP_MTHI:
      return "mthi $" + std::to_string(instruction.reg.rs);
    case FULL_OP_MTLO:
      return "mtlo $" + std::to_string(instruction.reg.rs);
    case FULL_OP_MULT:
      return "mult $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_MULTU:
      return "multu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_NOR:
      return "nor $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_OR:
      return "or $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_SLL:
      return "sll $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_SLLV:
      return "sllv $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_SLT:
      return "slt $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_SLTU:
      return "sltu $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_SRA:
      return "sra $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_SRAV:
      return "srav $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_SRL:
      return "srl $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", " + std::to_string(instruction.reg.sa);
    case FULL_OP_SRLV:
      return "srlv $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rt) + ", $" + std::to_string(instruction.reg.rs);
    case FULL_OP_SUB:
      return "sub $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_SUBU:
      return "subu $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_SYSCALL:
      return "syscall";
    case FULL_OP_XOR:
      return "xor $" + std::to_string(instruction.reg.rd) + ", $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TGE:
      return "tge $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TGEU:
      return "tgeu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TLT:
      return "tlt $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TLTU:
      return "tltu $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TEQ:
      return "teq $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    case FULL_OP_TNE:
      return "tne $" + std::to_string(instruction.reg.rs) + ", $" + std::to_string(instruction.reg.rt);
    default:
      throw std::runtime_error("Invalid register instruction");
  }
}

std::string disassemble_immediate(Instruction const& instruction) {
  switch (instruction.full_op) {
    case FULL_OP_ADDI:
      return "addi $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_ADDIU:
      return "addiu $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_ANDI:
      return "andi $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BEQ:
      return "beq $" + std::to_string(instruction.immediate.rs) + ", $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BEQL:
      return "beql $" + std::to_string(instruction.immediate.rs) + ", $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BGTZ:
      return "bgtz $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BGTZL:
      return "bgtzl $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BLEZ:
      return "blez $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BLEZL:
      return "blezl $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BNE:
      return "bne $" + std::to_string(instruction.immediate.rs) + ", $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_BNEL:
      return "bnel $" + std::to_string(instruction.immediate.rs) + ", $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_DADDI:
      return "daddi $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_DADDIU:
      return "daddiu $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_LB:
      return "lb $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LBU:
      return "lbu $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LD:
      return "ld $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LDL:
      return "ldl $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LDR:
      return "ldr $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LH:
      return "lh $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LHU:
      return "lhu $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LL:
      return "ll $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LLD:
      return "lld $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LUI:
      return "lui $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_LW:
      return "lw $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LWL:
      return "lwl $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LWR:
      return "lwr $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_LWU:
      return "lwu $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_ORI:
      return "ori $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_SB:
      return "sb $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SC:
      return "sc $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SCD:
      return "scd $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SD:
      return "sd $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SDL:
      return "sdl $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SDR:
      return "sdr $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SH:
      return "sh $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SLTI:
      return "slti $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_SLTIU:
      return "sltiu $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    case FULL_OP_SW:
      return "sw $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SWL:
      return "swl $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_SWR:
      return "swr $" + std::to_string(instruction.immediate.rt) + ", " + format_hex(instruction.immediate.immediate) + "($" + std::to_string(instruction.immediate.rs) + ")";
    case FULL_OP_XORI:
      return "xori $" + std::to_string(instruction.immediate.rt) + ", $" + std::to_string(instruction.immediate.rs) + ", " + format_hex(instruction.immediate.immediate);
    default:
      throw std::runtime_error("Invalid immediate instruction");
  }
}

std::string disassemble_jump(Instruction const& instruction) {
  switch (instruction.full_op) {
    case FULL_OP_J:
      return "j " + format_hex(instruction.jump.target);
    case FULL_OP_JAL:
      return "jal " + format_hex(instruction.jump.target);
    default:
      throw std::runtime_error("Invalid jump instruction");
  }
}

std::string disassemble_register_immediate(Instruction const& instruction) {
  switch (instruction.full_op) {
    case FULL_OP_BLTZ:
      return "bltz $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BGEZ:
      return "bgez $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BLTZL:
      return "bltzl $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BGEZL:
      return "bgezl $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TGEI:
      return "tgei $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TGEIU:
      return "tgeiu $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TLTI:
      return "tlti $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TLTIU:
      return "tltiu $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TEQI:
      return "teqi $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_TNEI:
      return "tnei $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BLTZAL:
      return "bltzal $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BGEZAL:
      return "bgezal $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BLTZALL:
      return "bltzall $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    case FULL_OP_BGEZALL:
      return "bgezall $" + std::to_string(instruction.regimm.rs) + ", " + format_hex(instruction.regimm.immediate);
    default:
      throw std::runtime_error("Invalid register immediate instruction");
  }
}

std::string disassemble_get_fpu_format(Instruction const& instruction) {
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

std::string disassemble_coprocessor(Instruction const& instruction) {
  switch (instruction.full_op) {
    // FPU instructions
    case FULL_OP_FADD:
      return "add." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.ft);
    case FULL_OP_FABS:
      return "abs." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CF:
      return "C.F." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.ft);
    case FULL_OP_CEILL:
      return "ceil.l." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CEILW:
      return "ceil.w." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CVTD:
      return "cvt.d." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CVTL:
      return "cvt.l." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CVTS:
      return "cvt.s." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_CVTW:
      return "cvt.w." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FDIV:
      return "div." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.ft);
    case FULL_OP_FLOORL:
      return "floor.l." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FLOORW:
      return "floor.w." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FMOV:
      return "mov." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FMUL:
      return "mul." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.ft);
    case FULL_OP_FNEG:
      return "neg." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_ROUNDL:
      return "round.l." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_ROUNDW:
      return "round.w." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FSQRT:
      return "sqrt." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_FSUB:
      return "sub." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.ft);
    case FULL_OP_TRUNCL:
      return "trunc.l." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    case FULL_OP_TRUNCW:
      return "trunc.w." + disassemble_get_fpu_format(instruction) + " $f" + std::to_string(instruction.coprocessor.cop_fpu.fd) + ", $f" + std::to_string(instruction.coprocessor.cop_fpu.fs);
    
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
      return "mtc0 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_MFC0:
      return "mfc0 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_DMTC0:
      return "dmfc0 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_DMFC0:
      return "dmfc0 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_CFC0:
      return "cfc0 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_CFC1:
      return "cfc1 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    case FULL_OP_CFC2:
      return "cfc2 $" + std::to_string(instruction.coprocessor.cop_op_register.rt) + ", " + std::to_string(instruction.coprocessor.cop_op_register.rd);
    
    case FULL_OP_BC0F:
      return "bc0f " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC1F:
      return "bc1f " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC2F:
      return "bc2f " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    
    case FULL_OP_BC0T:
      return "bc0t " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC1T:
      return "bc1t " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC2T:
      return "bc2t " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    
    case FULL_OP_BC0FL:
      return "bc0fl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC1FL:
      return "bc1fl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC2FL:
      return "bc2fl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);

    case FULL_OP_BC0TL:
      return "bc0tl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC1TL:
      return "bc1tl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    case FULL_OP_BC2TL:
      return "bc2tl " + format_hex(instruction.coprocessor.cop_op_no_register.immediate);
    
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

std::string disassemble_cache(Instruction const& instruction) {
  if (instruction.full_op < FULL_OP_CACHE_INDEX_INVALIDATE || instruction.full_op > FULL_OP_CACHE_HIT_WRITE_BACK_DATA_CACHE) {
    throw std::runtime_error("Invalid cache instruction");
  }
  return "cache " + std::to_string(instruction.cache.cache_op) + ", " + format_hex(instruction.cache.offset) + "($" + std::to_string(instruction.cache.base) + ")";
}

std::string disassemble(Instruction const& instruction) {
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
    default:
      throw std::runtime_error("Invalid instruction type");
  }
}