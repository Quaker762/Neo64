#include "decoder.h"
#include <stdexcept>

static FullOp special_op_table[8][8] = {
    {FULL_OP_SLL, FULL_OP_INVALID, FULL_OP_SRL, FULL_OP_SRA, FULL_OP_SLLV,
     FULL_OP_INVALID, FULL_OP_SRLV, FULL_OP_SRAV},
    {FULL_OP_JR, FULL_OP_JALR, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_SYSCALL, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_BREAK},
    {FULL_OP_MFHI, FULL_OP_MTHI, FULL_OP_MFLO, FULL_OP_MTLO, FULL_OP_DSLLV,
     FULL_OP_INVALID, FULL_OP_DSRLV, FULL_OP_DSRAV},
    {FULL_OP_MULT, FULL_OP_MULTU, FULL_OP_DIV, FULL_OP_DIVU, FULL_OP_DMULT,
     FULL_OP_DMULTU, FULL_OP_DDIV, FULL_OP_DDIVU},
    {FULL_OP_ADD, FULL_OP_ADDU, FULL_OP_SUB, FULL_OP_SUBU, FULL_OP_AND,
     FULL_OP_OR, FULL_OP_XOR, FULL_OP_NOR},
    {FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_SLT, FULL_OP_SLTU, FULL_OP_DADD,
     FULL_OP_DADDU, FULL_OP_DSUB, FULL_OP_DSUBU},
    {FULL_OP_TGE, FULL_OP_TGEU, FULL_OP_TLT, FULL_OP_TLTU, FULL_OP_TEQ,
     FULL_OP_INVALID, FULL_OP_TNE, FULL_OP_INVALID},
    {FULL_OP_DSLL, FULL_OP_INVALID, FULL_OP_DSRL, FULL_OP_DSRA, FULL_OP_DSLL32,
     FULL_OP_INVALID, FULL_OP_DSRL32, FULL_OP_DSRA32}};

// A.K.A SPECIAL Function
Instruction mips_decode_register_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_REGISTER;
  populate_register_instruction(&instruction_data.reg, instruction);

  uint8_t group = (instruction >> 3) & 0x7;
  uint8_t sub_group = instruction & 0x7;
  instruction_data.full_op = special_op_table[group][sub_group];

  return instruction_data;
}

static FullOp regimm_op_table[3][8] = {
    {FULL_OP_BLTZ, FULL_OP_BGEZ, FULL_OP_BLTZL, FULL_OP_BGEZL},
    {FULL_OP_TGEI, FULL_OP_TGEIU, FULL_OP_TLTI, FULL_OP_TLTIU, FULL_OP_TEQI,
     FULL_OP_INVALID, FULL_OP_TNEI},
    {FULL_OP_BLTZAL, FULL_OP_BGEZAL, FULL_OP_BLTZALL, FULL_OP_BGEZALL}};

Instruction mips_decode_regimm(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_REGISTER_IMMEDIATE;
  populate_register_immediate_instruction(&instruction_data.regimm,
                                          instruction);

  uint8_t group = (instruction >> 19) & 0x3;
  uint8_t sub_group = (instruction >> 16) & 0x7;
  instruction_data.full_op = regimm_op_table[group][sub_group];

  return instruction_data;
}

Instruction mips_decode_cache_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_CACHE;
  populate_cache_instruction(&instruction_data.cache, instruction);

  switch (instruction_data.cache.cache_op) {
  case CACHE_OP_INDEX_INVALIDATE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_INVALIDATE;
    break;
  case CACHE_OP_INDEX_WRITE_BACK_INVALIDATE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_WRITE_BACK_INVALIDATE;
    break;
  case CACHE_OP_INDEX_LOAD_TAG_INSTRUCTION_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_LOAD_TAG_INSTRUCTION_CACHE;
    break;
  case CACHE_OP_INDEX_LOAD_TAG_DATA_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_LOAD_TAG_DATA_CACHE;
    break;
  case CACHE_OP_INDEX_STORE_TAG_INSTRUCTION_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_STORE_TAG_INSTRUCTION_CACHE;
    break;
  case CACHE_OP_INDEX_STORE_TAG_DATA_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_INDEX_STORE_TAG_DATA_CACHE;
    break;
  case CACHE_OP_CREATE_DIRTY_EXCLUSIVE:
    instruction_data.full_op = FULL_OP_CACHE_CREATE_DIRTY_EXCLUSIVE;
    break;
  case CACHE_OP_HIT_INVALIDATE_INSTRUCTION_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_HIT_INVALIDATE_INSTRUCTION_CACHE;
    break;
  case CACHE_OP_HIT_INVALIDATE_DATA_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_HIT_INVALIDATE_DATA_CACHE;
    break;
  case CACHE_OP_HIT_WRITE_BACK_INVALIDATE:
    instruction_data.full_op = FULL_OP_CACHE_HIT_WRITE_BACK_INVALIDATE;
    break;
  case CACHE_OP_FILL:
    instruction_data.full_op = FULL_OP_CACHE_FILL;
    break;
  case CACHE_OP_HIT_WRITE_BACK_INSTRUCTION_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_HIT_WRITE_BACK_INSTRUCTION_CACHE;
    break;
  case CACHE_OP_HIT_WRITE_BACK_DATA_CACHE:
    instruction_data.full_op = FULL_OP_CACHE_HIT_WRITE_BACK_DATA_CACHE;
    break;
  default:
    throw std::runtime_error("Invalid cache operation");
  }

  return instruction_data;
}

template <FullOp full_op>
Instruction mips_decode_jump_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_JUMP;
  populate_jump_instruction(&instruction_data.jump, instruction);
  instruction_data.full_op = full_op;
  return instruction_data;
}

template <FullOp full_op>
Instruction mips_decode_immediate_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_IMMEDIATE;
  populate_immediate_instruction(&instruction_data.immediate, instruction);
  instruction_data.full_op = full_op;
  return instruction_data;
}

static CoprocessorType coprocessor_op_table[2][8] = {
    {
        COP_TYPE_OP_REGISTER, // MF
        COP_TYPE_OP_REGISTER, // DMF
        COP_TYPE_OP_REGISTER, // CF
        COP_TYPE_OP_REGISTER, // MT
        COP_TYPE_OP_REGISTER, // DMT
        COP_TYPE_OP_REGISTER, // CT
    },
    {
        COP_TYPE_OP_NO_REGISTER, // BC
    },
};

static FullOp cop0_op_table[4][7] = {
    {FULL_OP_INVALID, FULL_OP_TLBR, FULL_OP_TLBWI, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_TLBWR},
    {FULL_OP_TLBP, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID},
    {FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID},
    {FULL_OP_ERET, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID}};

static FullOp fpu_op_table[8][8] = {
    {// Row 0
     FULL_OP_FADD, FULL_OP_FSUB, FULL_OP_FMUL, FULL_OP_FDIV, FULL_OP_FSQRT,
     FULL_OP_FABS, FULL_OP_FMOV, FULL_OP_FNEG},
    {// Row 1
     FULL_OP_ROUNDL, FULL_OP_TRUNCL, FULL_OP_CEILL, FULL_OP_FLOORL,
     FULL_OP_ROUNDW, FULL_OP_TRUNCW, FULL_OP_CEILW, FULL_OP_FLOORW},
    {// Row 2
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID},
    {// Row 3
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID},
    {// Row 4
     FULL_OP_CVTS, FULL_OP_CVTD, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_CVTW,
     FULL_OP_CVTL, FULL_OP_INVALID, FULL_OP_INVALID},
    {// Row 5
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID,
     FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID, FULL_OP_INVALID},
    {// Row 6
     FULL_OP_CF, FULL_OP_CUN, FULL_OP_CEQ, FULL_OP_CUEQ, FULL_OP_COLT,
     FULL_OP_CULT, FULL_OP_COLE, FULL_OP_CULE},
    {// Row 7
     FULL_OP_CSF, FULL_OP_CNGLE, FULL_OP_CSEQ, FULL_OP_CNGL, FULL_OP_CLT,
     FULL_OP_CNGE, FULL_OP_CLE, FULL_OP_CNGT}};

#define MAP_COP_INSTRUCTION(base_op, suffix)                                   \
  switch (proc_num) {                                                          \
  case 0: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##0##suffix;            \
    break;                                                                     \
  }                                                                            \
  case 1: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##1##suffix;            \
    break;                                                                     \
  }                                                                            \
  case 2: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##2##suffix;            \
    break;                                                                     \
  }                                                                            \
  }

#define MAP_COP_INSTRUCTION_NO_SUFFIX(base_op)                                 \
  switch (proc_num) {                                                          \
  case 0: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##0;                    \
    break;                                                                     \
  }                                                                            \
  case 1: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##1;                    \
    break;                                                                     \
  }                                                                            \
  case 2: {                                                                    \
    coprocessor_instruction.full_op = FULL_OP_##base_op##2;                    \
    break;                                                                     \
  }                                                                            \
  }

Instruction mips_decode_coprocessor_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_COPROCESSOR;

  CoprocessorInstruction coprocessor_instruction;
  uint8_t group = (instruction >> 24) & 0x3;
  uint8_t sub_group = (instruction >> 21) & 0x7;
  uint8_t proc_num = (instruction >> 26) & 0x3;

  if (group >= 2) {
    if (proc_num == 1) {
      coprocessor_instruction.type = COP_TYPE_FPU;
      populate_coprocessor_fpu_instruction(&coprocessor_instruction.cop_fpu,
                                           instruction);

      uint8_t fpu_group = (instruction >> 3) & 0x7;
      uint8_t fpu_sub_group = instruction & 0x7;
      coprocessor_instruction.full_op = fpu_op_table[fpu_group][fpu_sub_group];
    } else {
      coprocessor_instruction.type = COP_TYPE_COFUNC;
      populate_coprocessor_co_func_instruction(
          &coprocessor_instruction.cop_co_func, instruction);

      if (proc_num == 0) {
        uint8_t cop0_group = (instruction >> 3) & 0x7;
        uint8_t cop0_sub_group = instruction & 0x7;
        coprocessor_instruction.full_op =
            cop0_op_table[cop0_group][cop0_sub_group];
      } else {
        MAP_COP_INSTRUCTION_NO_SUFFIX(COP)
      }
    }
  } else {
    coprocessor_instruction.type = coprocessor_op_table[group][sub_group];
    switch (coprocessor_instruction.type) {
    case COP_TYPE_OP_NO_REGISTER: {
      populate_coprocessor_op_no_register_instruction(
          &coprocessor_instruction.cop_op_no_register, instruction);
      // Decode the full operation.
      switch (coprocessor_instruction.cop_op_no_register.sub_op) {
      case COP_OP_BCF: {
        MAP_COP_INSTRUCTION(BC, F)
        break;
      }
      case COP_OP_BCT: {
        MAP_COP_INSTRUCTION(BC, T)
        break;
      }
      case COP_OP_BCFL: {
        MAP_COP_INSTRUCTION(BC, FL)
        break;
      }
      case COP_OP_BCTL: {
        MAP_COP_INSTRUCTION(BC, TL)
        break;
      }
      default:
        throw std::runtime_error("Invalid coprocessor operation (1)");
      }
      break;
    }
    case COP_TYPE_OP_REGISTER: {
      populate_coprocessor_op_register_instruction(
          &coprocessor_instruction.cop_op_register, instruction);
      // Decode the full operation.
      switch (coprocessor_instruction.cop_op_register.cop_op) {
      case COP_CF: {
        MAP_COP_INSTRUCTION_NO_SUFFIX(CFC)
        break;
      }
      case COP_MT: {
        coprocessor_instruction.full_op = FULL_OP_MTC0;
        break;
      }
      case COP_MF: {
        coprocessor_instruction.full_op = FULL_OP_MFC0;
        break;
      }
      case COP_DMT: {
        coprocessor_instruction.full_op = FULL_OP_DMTC0;
        break;
      }
      case COP_DMF: {
        coprocessor_instruction.full_op = FULL_OP_DMFC0;
        break;
      }
      default:
        throw std::runtime_error("Invalid coprocessor operation (2)");
      }
      break;
    }
    default:
      throw std::runtime_error("Should not get here");
    }
  }

  instruction_data.coprocessor = coprocessor_instruction;
  return instruction_data;
}

// See figure 16-1 in 16.7.
static Instruction (*mips_decode_table[8][8])(uint32_t) = {
    {
        mips_decode_register_type,                // SPECIAL
        mips_decode_regimm,                       // REGIMM
        mips_decode_jump_type<FULL_OP_J>,         // J
        mips_decode_jump_type<FULL_OP_JAL>,       // JAL
        mips_decode_immediate_type<FULL_OP_BEQ>,  // BEQ
        mips_decode_immediate_type<FULL_OP_BNE>,  // BNE
        mips_decode_immediate_type<FULL_OP_BLEZ>, // BLEZ
        mips_decode_immediate_type<FULL_OP_BGTZ>  // BGTZ
    },
    {
        mips_decode_immediate_type<FULL_OP_ADDI>,  // ADDI
        mips_decode_immediate_type<FULL_OP_ADDIU>, // ADDIU
        mips_decode_immediate_type<FULL_OP_SLTI>,  // SLTI
        mips_decode_immediate_type<FULL_OP_SLTIU>, // SLTIU
        mips_decode_immediate_type<FULL_OP_ANDI>,  // ANDI
        mips_decode_immediate_type<FULL_OP_ORI>,   // ORI
        mips_decode_immediate_type<FULL_OP_XORI>,  // XORI
        mips_decode_immediate_type<FULL_OP_LUI>    // LUI
    },
    {
        mips_decode_coprocessor_type,              // COP0
        mips_decode_coprocessor_type,              // COP1
        mips_decode_coprocessor_type,              // COP2
        mips_decode_coprocessor_type,              // COP3
        mips_decode_immediate_type<FULL_OP_BEQL>,  // BEQL
        mips_decode_immediate_type<FULL_OP_BNEL>,  // BNEL
        mips_decode_immediate_type<FULL_OP_BLEZL>, // BLEZL
        mips_decode_immediate_type<FULL_OP_BGTZL>  // BGTZL
    },
    {mips_decode_immediate_type<FULL_OP_DADDI>,  // DADDI
     mips_decode_immediate_type<FULL_OP_DADDIU>, // DADDIU
     mips_decode_immediate_type<FULL_OP_LDL>,    // LDL
     mips_decode_immediate_type<FULL_OP_LDR>,    // LDR
     nullptr, nullptr, nullptr, nullptr},
    {
        mips_decode_immediate_type<FULL_OP_LB>,  // LB
        mips_decode_immediate_type<FULL_OP_LH>,  // LH
        mips_decode_immediate_type<FULL_OP_LWL>, // LWL
        mips_decode_immediate_type<FULL_OP_LW>,  // LW
        mips_decode_immediate_type<FULL_OP_LBU>, // LBU
        mips_decode_immediate_type<FULL_OP_LHU>, // LHU
        mips_decode_immediate_type<FULL_OP_LWR>, // LWR
        mips_decode_immediate_type<FULL_OP_LWU>  // LWU
    },
    {
        mips_decode_immediate_type<FULL_OP_SB>,  // SB
        mips_decode_immediate_type<FULL_OP_SH>,  // SH
        mips_decode_immediate_type<FULL_OP_SWL>, // SWL
        mips_decode_immediate_type<FULL_OP_SW>,  // SW
        mips_decode_immediate_type<FULL_OP_SDL>, // SDL
        mips_decode_immediate_type<FULL_OP_SDR>, // SDR
        mips_decode_immediate_type<FULL_OP_SWR>, // SWR
        mips_decode_cache_type                   // CACHE
    },
    {
        mips_decode_immediate_type<FULL_OP_LL>,   // LL
        mips_decode_immediate_type<FULL_OP_LWC1>, // LWC1
        mips_decode_immediate_type<FULL_OP_LWC2>, // LWC2
        nullptr,
        mips_decode_immediate_type<FULL_OP_LLD>,  // LLD
        mips_decode_immediate_type<FULL_OP_LDC1>, // LDC1
        mips_decode_immediate_type<FULL_OP_LDC2>, // LDC2
        mips_decode_immediate_type<FULL_OP_LD>    // LD
    },
    {
        mips_decode_immediate_type<FULL_OP_SC>,   // SC
        mips_decode_immediate_type<FULL_OP_SWC1>, // SWC1
        mips_decode_immediate_type<FULL_OP_SWC2>, // SWC2
        nullptr,
        mips_decode_immediate_type<FULL_OP_SCD>,  // SCD
        mips_decode_immediate_type<FULL_OP_SDC1>, // SDC1
        mips_decode_immediate_type<FULL_OP_SDC2>, // SDC2
        mips_decode_immediate_type<FULL_OP_SD>    // SD
    }};

Instruction mips_decode(uint32_t instruction) {
  // 31..29 - Vertical columns in figure 16-1 (Opcode).
  uint8_t group = (instruction >> 29) & 0x7;

  // 28..26 - Horizontal columns in figure 16-1 (Opcode).
  uint8_t sub_group = (instruction >> 26) & 0x7;

  return mips_decode_table[group][sub_group](instruction);
}
