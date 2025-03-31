#include "decoder.h"
#include <stdexcept>

static FullOp special_op_table[8][8] = {
  [0][0] = FULL_OP_SLL,
  [0][2] = FULL_OP_SRL,
  [0][3] = FULL_OP_SRA,
  [0][4] = FULL_OP_SLLV,
  [0][6] = FULL_OP_SRLV,
  [0][7] = FULL_OP_SRAV,

  [1][0] = FULL_OP_JR,
  [1][1] = FULL_OP_JALR,
  [1][4] = FULL_OP_SYSCALL,
  [1][7] = FULL_OP_BREAK,

  [2][0] = FULL_OP_MFHI,
  [2][1] = FULL_OP_MTHI,
  [2][2] = FULL_OP_MFLO,
  [2][3] = FULL_OP_MTLO,
  [2][4] = FULL_OP_DSLLV,
  [2][6] = FULL_OP_DSRLV,
  [2][7] = FULL_OP_DSRAV,

  [3][0] = FULL_OP_MULT,
  [3][1] = FULL_OP_MULTU,
  [3][2] = FULL_OP_DIV,
  [3][3] = FULL_OP_DIVU,
  [3][4] = FULL_OP_DMULT,
  [3][5] = FULL_OP_DMULTU,
  [3][6] = FULL_OP_DDIV,
  [3][7] = FULL_OP_DDIVU,

  [4][0] = FULL_OP_ADD,
  [4][1] = FULL_OP_ADDU,
  [4][2] = FULL_OP_SUB,
  [4][3] = FULL_OP_SUBU,
  [4][4] = FULL_OP_AND,
  [4][5] = FULL_OP_OR,
  [4][6] = FULL_OP_XOR,
  [4][7] = FULL_OP_NOR,

  [5][2] = FULL_OP_SLT,
  [5][3] = FULL_OP_SLTU,
  [5][4] = FULL_OP_DADD,
  [5][5] = FULL_OP_DADDU,
  [5][6] = FULL_OP_DSUB,
  [5][7] = FULL_OP_DSUBU,

  [6][0] = FULL_OP_TGE,
  [6][1] = FULL_OP_TGEU,
  [6][2] = FULL_OP_TLT,
  [6][3] = FULL_OP_TLTU,
  [6][4] = FULL_OP_TEQ,
  [6][6] = FULL_OP_TNE,
  
  [7][0] = FULL_OP_DSLL,
  [7][2] = FULL_OP_DSRL,
  [7][3] = FULL_OP_DSRA,
  [7][4] = FULL_OP_DSLL32,
  [7][6] = FULL_OP_DSRL32,
  [7][7] = FULL_OP_DSRA32,
};

// A.K.A SPECIAL Function
Instruction mips_decode_register_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_REGISTER;
  instruction_data.reg = *(RegisterInstruction*)&instruction;

  uint8_t group = (instruction >> 3) & 0x7;
  uint8_t sub_group = instruction & 0x7;
  instruction_data.full_op = special_op_table[group][sub_group];

  return instruction_data;
}

static FullOp regimm_op_table[3][8] = {
  [0][0] = FULL_OP_BLTZ,
  [0][1] = FULL_OP_BGEZ,
  [0][2] = FULL_OP_BLTZL,
  [0][3] = FULL_OP_BGEZL,
  
  [1][0] = FULL_OP_TGEI,
  [1][1] = FULL_OP_TGEIU,
  [1][2] = FULL_OP_TLTI,
  [1][3] = FULL_OP_TLTIU,
  [1][4] = FULL_OP_TEQI,
  [1][6] = FULL_OP_TNEI,

  [2][0] = FULL_OP_BLTZAL,
  [2][1] = FULL_OP_BGEZAL,
  [2][2] = FULL_OP_BLTZALL,
  [2][3] = FULL_OP_BGEZALL,
};

Instruction mips_decode_regimm(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_REGISTER_IMMEDIATE;
  instruction_data.regimm = *(RegisterImmediateInstruction*)&instruction;

  uint8_t group = (instruction >> 19) & 0x3;
  uint8_t sub_group = (instruction >> 16) & 0x7;
  instruction_data.full_op = regimm_op_table[group][sub_group];

  return instruction_data;
}

Instruction mips_decode_cache_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_CACHE;
  instruction_data.cache = *(CacheInstruction*)&instruction;

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
  instruction_data.jump = *(JumpInstruction*)&instruction;
  instruction_data.full_op = full_op;
  return instruction_data;
}

template <FullOp full_op>
Instruction mips_decode_immediate_type(uint32_t instruction) {
  Instruction instruction_data;
  instruction_data.type = TYPE_IMMEDIATE;
  instruction_data.immediate = *(ImmediateInstruction*)&instruction;
  instruction_data.full_op = full_op;
  return instruction_data;
}

static CoprocessorType coprocessor_op_table[4][8] = {
  [0][0] = COP_TYPE_OP_REGISTER, // MF
  [0][1] = COP_TYPE_OP_REGISTER, // DMF
  [0][2] = COP_TYPE_OP_REGISTER, // CF
  [0][4] = COP_TYPE_OP_REGISTER, // MT
  [0][5] = COP_TYPE_OP_REGISTER, // DMT
  [0][6] = COP_TYPE_OP_REGISTER, // CT

  [1][0] = COP_TYPE_OP_NO_REGISTER, // BC
};

static FullOp cop0_op_table[4][7] = {
  [0][1] = FULL_OP_TLBR,
  [0][2] = FULL_OP_TLBWI,
  [0][6] = FULL_OP_TLBWR,
  [1][0] = FULL_OP_TLBP,
  [3][0] = FULL_OP_ERET,
};

static FullOp fpu_op_table[8][8] = {
  [0][0] = FULL_OP_FADD,
  [0][1] = FULL_OP_FSUB,
  [0][2] = FULL_OP_FMUL,
  [0][3] = FULL_OP_FDIV,
  [0][4] = FULL_OP_FSQRT,
  [0][5] = FULL_OP_FABS,
  [0][6] = FULL_OP_FMOV,
  [0][7] = FULL_OP_FNEG,

  [1][0] = FULL_OP_ROUNDL,
  [1][1] = FULL_OP_TRUNCL,
  [1][2] = FULL_OP_CEILL,
  [1][3] = FULL_OP_FLOORL,
  [1][4] = FULL_OP_ROUNDW,
  [1][5] = FULL_OP_TRUNCW,
  [1][6] = FULL_OP_CEILW,
  [1][7] = FULL_OP_FLOORW,

  [4][0] = FULL_OP_CVTS,
  [4][1] = FULL_OP_CVTD,
  [4][4] = FULL_OP_CVTW,
  [4][5] = FULL_OP_CVTL,

  [6][0] = FULL_OP_CF,
  [6][1] = FULL_OP_CUN,
  [6][2] = FULL_OP_CEQ,
  [6][3] = FULL_OP_CUEQ,
  [6][4] = FULL_OP_COLT,
  [6][5] = FULL_OP_CULT,
  [6][6] = FULL_OP_COLE,
  [6][7] = FULL_OP_CULE,

  [7][0] = FULL_OP_CSF,
  [7][1] = FULL_OP_CNGLE,
  [7][2] = FULL_OP_CSEQ,
  [7][3] = FULL_OP_CNGL,
  [7][4] = FULL_OP_CLT,
  [7][5] = FULL_OP_CNGE,
  [7][6] = FULL_OP_CLE,
  [7][7] = FULL_OP_CNGT,
};

#define MAP_COP_INSTRUCTION(base_op, suffix) \
  switch (proc_num) { \
    case 0: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##0##suffix; \
      break; \
    } \
    case 1: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##1##suffix; \
      break; \
    } \
    case 2: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##2##suffix; \
      break; \
    } \
  }

#define MAP_COP_INSTRUCTION_NO_SUFFIX(base_op) \
  switch (proc_num) { \
    case 0: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##0; \
      break; \
    } \
    case 1: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##1; \
      break; \
    } \
    case 2: { \
      coprocessor_instruction.full_op = FULL_OP_##base_op##2; \
      break; \
    } \
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
      coprocessor_instruction.cop_fpu = *(CoprocessorFPUInstruction*)&instruction;

      uint8_t fpu_group = (instruction >> 3) & 0x7;
      uint8_t fpu_sub_group = instruction & 0x7;
      coprocessor_instruction.full_op = fpu_op_table[fpu_group][fpu_sub_group];
    } else {
      coprocessor_instruction.type = COP_TYPE_COFUNC;
      coprocessor_instruction.cop_co_func = *(CoprocessorCoFuncInstruction*)&instruction;

      if (proc_num == 0) {
        uint8_t cop0_group = (instruction >> 3) & 0x7;
        uint8_t cop0_sub_group = instruction & 0x7;
        coprocessor_instruction.full_op = cop0_op_table[cop0_group][cop0_sub_group];
      } else {
        MAP_COP_INSTRUCTION_NO_SUFFIX(COP)
      }
    }
  } else {
    coprocessor_instruction.type = coprocessor_op_table[group][sub_group];
    switch (coprocessor_instruction.type) {
      case COP_TYPE_OP_NO_REGISTER: {
        coprocessor_instruction.cop_op_no_register = *(CoprocessorOpNoRegisterInstruction*)&instruction;
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
        coprocessor_instruction.cop_op_register = *(CoprocessorOpRegisterInstruction*)&instruction;
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
  return instruction_data;
}

// See figure 16-1 in 16.7.
static Instruction (*mips_decode_table[8][8])(uint32_t) = {
  [0][0] = mips_decode_register_type,                  // SPECIAL
  [1][0] = mips_decode_regimm,                         // REGIMM
  [2][0] = mips_decode_jump_type<FULL_OP_J>,           // J
  [3][0] = mips_decode_jump_type<FULL_OP_JAL>,         // JAL
  [4][0] = mips_decode_immediate_type<FULL_OP_BEQ>,    // BEQ
  [5][0] = mips_decode_immediate_type<FULL_OP_BNE>,    // BNE
  [6][0] = mips_decode_immediate_type<FULL_OP_BLEZ>,   // BLEZ
  [7][0] = mips_decode_immediate_type<FULL_OP_BGTZ>,   // BGTZ

  [0][1] = mips_decode_immediate_type<FULL_OP_ADDI>,   // ADDI
  [1][1] = mips_decode_immediate_type<FULL_OP_ADDIU>,  // ADDIU
  [2][1] = mips_decode_immediate_type<FULL_OP_SLTI>,   // SLTI
  [3][1] = mips_decode_immediate_type<FULL_OP_SLTIU>,  // SLTIU
  [4][1] = mips_decode_immediate_type<FULL_OP_ANDI>,   // ANDI
  [5][1] = mips_decode_immediate_type<FULL_OP_ORI>,    // ORI
  [6][1] = mips_decode_immediate_type<FULL_OP_XORI>,   // XORI
  [7][1] = mips_decode_immediate_type<FULL_OP_LUI>,    // LUI

  [0][2] = mips_decode_coprocessor_type,               // COP0
  [1][2] = mips_decode_coprocessor_type,               // COP1
  [2][2] = mips_decode_coprocessor_type,               // COP2
  [3][2] = mips_decode_coprocessor_type,               // COP3
  [4][2] = mips_decode_immediate_type<FULL_OP_BEQL>,   // BEQL 
  [5][2] = mips_decode_immediate_type<FULL_OP_BNEL>,   // BNEL
  [6][2] = mips_decode_immediate_type<FULL_OP_BLEZL>,  // BLEZL
  [7][2] = mips_decode_immediate_type<FULL_OP_BGTZL>,  // BGTZL

  [0][3] = mips_decode_immediate_type<FULL_OP_DADDI>,  // DADDI
  [1][3] = mips_decode_immediate_type<FULL_OP_DADDIU>, // DADDIU
  [2][3] = mips_decode_immediate_type<FULL_OP_LDL>,    // LDL
  [3][3] = mips_decode_immediate_type<FULL_OP_LDR>,    // LDR

  [0][4] = mips_decode_immediate_type<FULL_OP_LB>,     // LB
  [1][4] = mips_decode_immediate_type<FULL_OP_LH>,     // LH
  [2][4] = mips_decode_immediate_type<FULL_OP_LWL>,    // LWL
  [3][4] = mips_decode_immediate_type<FULL_OP_LW>,     // LW
  [4][4] = mips_decode_immediate_type<FULL_OP_LBU>,    // LBU
  [5][4] = mips_decode_immediate_type<FULL_OP_LHU>,    // LHU
  [6][4] = mips_decode_immediate_type<FULL_OP_LWR>,    // LWR
  [7][4] = mips_decode_immediate_type<FULL_OP_LWU>,    // LWU

  [0][5] = mips_decode_immediate_type<FULL_OP_SB>,     // SB
  [1][5] = mips_decode_immediate_type<FULL_OP_SH>,     // SH
  [2][5] = mips_decode_immediate_type<FULL_OP_SWL>,    // SWL
  [3][5] = mips_decode_immediate_type<FULL_OP_SW>,     // SW
  [4][5] = mips_decode_immediate_type<FULL_OP_SDL>,    // SDL
  [5][5] = mips_decode_immediate_type<FULL_OP_SDR>,    // SDR
  [6][5] = mips_decode_immediate_type<FULL_OP_SWR>,    // SWR
  [7][5] = mips_decode_cache_type,                     // CACHE

  [0][6] = mips_decode_immediate_type<FULL_OP_LL>,     // LL
  [1][6] = mips_decode_immediate_type<FULL_OP_LWC1>,   // LWC1
  [2][6] = mips_decode_immediate_type<FULL_OP_LWC2>,   // LWC2
  [4][6] = mips_decode_immediate_type<FULL_OP_LLD>,    // LLD
  [5][6] = mips_decode_immediate_type<FULL_OP_LDC1>,   // LDC1
  [6][6] = mips_decode_immediate_type<FULL_OP_LDC2>,   // LDC2
  [7][6] = mips_decode_immediate_type<FULL_OP_LD>,     // LD

  [0][7] = mips_decode_immediate_type<FULL_OP_SC>,     // SC
  [1][7] = mips_decode_immediate_type<FULL_OP_SWC1>,   // SWC1
  [2][7] = mips_decode_immediate_type<FULL_OP_SWC2>,   // SWC2
  [4][7] = mips_decode_immediate_type<FULL_OP_SCD>,    // SCD
  [5][7] = mips_decode_immediate_type<FULL_OP_SDC1>,   // SDC1
  [6][7] = mips_decode_immediate_type<FULL_OP_SDC2>,   // SDC2
  [7][7] = mips_decode_immediate_type<FULL_OP_SD>,     // SD
};

Instruction mips_decode(uint32_t instruction) {
  // 28..26 - Horizontal columns in figure 16-1 (Opcode).
  uint8_t group = (instruction >> 26) & 0x7;

  // 31..29 - Vertical columns in figure 16-1 (Opcode).
  uint8_t sub_group = (instruction >> 29) & 0x7;

  return mips_decode_table[group][sub_group](instruction);
}
