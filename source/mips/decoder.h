#pragma once

#include "emu_types.h"

enum FullOp {
  // For invalid instruction detection
  FULL_OP_INVALID,

  // No-op instruction (0x00000000)
  FULL_OP_NOOP,

  // R-type instructions
  FULL_OP_ADD,
  FULL_OP_ADDU,
  FULL_OP_AND,
  FULL_OP_BREAK,
  FULL_OP_DADD,
  FULL_OP_DADDU,
  FULL_OP_DDIV,
  FULL_OP_DDIVU,
  FULL_OP_DIV,
  FULL_OP_DIVU,
  FULL_OP_DMULT,
  FULL_OP_DMULTU,
  FULL_OP_DSLL,
  FULL_OP_DSLL32,
  FULL_OP_DSLLV,
  FULL_OP_DSRA,
  FULL_OP_DSRA32,
  FULL_OP_DSRAV,
  FULL_OP_DSRL,
  FULL_OP_DSRL32,
  FULL_OP_DSRLV,
  FULL_OP_DSUB,
  FULL_OP_DSUBU,
  FULL_OP_JALR,
  FULL_OP_JR,
  FULL_OP_MFHI,
  FULL_OP_MFLO,
  FULL_OP_MOVN,
  FULL_OP_MOVZ,
  FULL_OP_MTHI,
  FULL_OP_MTLO,
  FULL_OP_MULT,
  FULL_OP_MULTU,
  FULL_OP_NOR,
  FULL_OP_OR,
  FULL_OP_SLL,
  FULL_OP_SLLV,
  FULL_OP_SLT,
  FULL_OP_SLTU,
  FULL_OP_SRA,
  FULL_OP_SRAV,
  FULL_OP_SRL,
  FULL_OP_SRLV,
  FULL_OP_SUB,
  FULL_OP_SUBU,
  FULL_OP_SYNC,
  FULL_OP_SYSCALL,
  FULL_OP_TEQ,
  FULL_OP_TGE,
  FULL_OP_TGEU,
  FULL_OP_TLT,
  FULL_OP_TLTU,
  FULL_OP_TNE,
  FULL_OP_XOR,

  // I-type instructions
  FULL_OP_ADDI,
  FULL_OP_ADDIU,
  FULL_OP_ANDI,
  FULL_OP_BEQ,
  FULL_OP_BEQL,
  FULL_OP_BGEZ,
  FULL_OP_BGEZAL,
  FULL_OP_BGEZALL,
  FULL_OP_BGEZL,
  FULL_OP_BGTZ,
  FULL_OP_BGTZL,
  FULL_OP_BLEZ,
  FULL_OP_BLEZL,
  FULL_OP_BLTZ,
  FULL_OP_BLTZAL,
  FULL_OP_BLTZALL,
  FULL_OP_BLTZL,
  FULL_OP_BNE,
  FULL_OP_BNEL,
  FULL_OP_DADDI,
  FULL_OP_DADDIU,
  FULL_OP_LB,
  FULL_OP_LBU,
  FULL_OP_LD,
  FULL_OP_LDL,
  FULL_OP_LDR,
  FULL_OP_LH,
  FULL_OP_LHU,
  FULL_OP_LL,
  FULL_OP_LLD,
  FULL_OP_LUI,
  FULL_OP_LW,
  FULL_OP_LWL,
  FULL_OP_LWR,
  FULL_OP_LWU,
  FULL_OP_ORI,
  FULL_OP_SB,
  FULL_OP_SC,
  FULL_OP_SCD,
  FULL_OP_SD,
  FULL_OP_SDL,
  FULL_OP_SDR,
  FULL_OP_SH,
  FULL_OP_SLTI,
  FULL_OP_SLTIU,
  FULL_OP_SW,
  FULL_OP_SWL,
  FULL_OP_SWR,
  FULL_OP_TEQI,
  FULL_OP_TGEI,
  FULL_OP_TGEIU,
  FULL_OP_TLTI,
  FULL_OP_TLTIU,
  FULL_OP_TNEI,
  FULL_OP_XORI,

  // J-type instructions
  FULL_OP_J,
  FULL_OP_JAL,

  // Coprocessor instructions
  FULL_OP_BC0T,
  FULL_OP_BC1T,
  FULL_OP_BC2T,
  FULL_OP_BC0TL,
  FULL_OP_BC1TL,
  FULL_OP_BC2TL,
  FULL_OP_BC0F,
  FULL_OP_BC1F,
  FULL_OP_BC2F,
  FULL_OP_BC0FL,
  FULL_OP_BC1FL,
  FULL_OP_BC2FL,
  FULL_OP_COP0,
  FULL_OP_COP1,
  FULL_OP_COP2,
  FULL_OP_COP3,
  FULL_OP_CFC0,
  FULL_OP_CFC1,
  FULL_OP_CFC2,
  FULL_OP_DMFC0,
  FULL_OP_DMTC0,
  FULL_OP_ERET,
  FULL_OP_LDC1,
  FULL_OP_LDC2,
  FULL_OP_LWC1,
  FULL_OP_LWC2,
  FULL_OP_MFC0,
  FULL_OP_MTC0,
  FULL_OP_SDC1,
  FULL_OP_SDC2,
  FULL_OP_SWC1,
  FULL_OP_SWC2,
  FULL_OP_TLBP,
  FULL_OP_TLBR,
  FULL_OP_TLBWI,
  FULL_OP_TLBWR,

  // Cache instructions (TODO: ORDER HERE IS COUPLED TO DISASSEMBLER, FIX THIS).
  FULL_OP_CACHE_INDEX_INVALIDATE,
  FULL_OP_CACHE_INDEX_WRITE_BACK_INVALIDATE,
  FULL_OP_CACHE_INDEX_LOAD_TAG_INSTRUCTION_CACHE,
  FULL_OP_CACHE_INDEX_LOAD_TAG_DATA_CACHE,
  FULL_OP_CACHE_INDEX_STORE_TAG_INSTRUCTION_CACHE,
  FULL_OP_CACHE_INDEX_STORE_TAG_DATA_CACHE,
  FULL_OP_CACHE_CREATE_DIRTY_EXCLUSIVE,
  FULL_OP_CACHE_HIT_INVALIDATE_INSTRUCTION_CACHE,
  FULL_OP_CACHE_HIT_INVALIDATE_DATA_CACHE,
  FULL_OP_CACHE_HIT_WRITE_BACK_INVALIDATE,
  FULL_OP_CACHE_FILL,
  FULL_OP_CACHE_HIT_WRITE_BACK_INSTRUCTION_CACHE,
  FULL_OP_CACHE_HIT_WRITE_BACK_DATA_CACHE,

  FULL_OP_FADD,
  FULL_OP_FSUB,
  FULL_OP_FMUL,
  FULL_OP_FDIV,
  FULL_OP_FSQRT,
  FULL_OP_FABS,
  FULL_OP_FMOV,
  FULL_OP_FNEG,
  FULL_OP_ROUNDL,
  FULL_OP_TRUNCL,
  FULL_OP_CEILL,
  FULL_OP_FLOORL,
  FULL_OP_ROUNDW,
  FULL_OP_TRUNCW,
  FULL_OP_CEILW,
  FULL_OP_FLOORW,
  FULL_OP_CVTS,
  FULL_OP_CVTD,
  FULL_OP_CVTW,
  FULL_OP_CVTL,
  FULL_OP_CF,
  FULL_OP_CUN,
  FULL_OP_CEQ,
  FULL_OP_CUEQ,
  FULL_OP_COLT,
  FULL_OP_CULT,
  FULL_OP_COLE,
  FULL_OP_CULE,
  FULL_OP_CSF,
  FULL_OP_CNGLE,
  FULL_OP_CSEQ,
  FULL_OP_CNGL,
  FULL_OP_CLT,
  FULL_OP_CNGE,
  FULL_OP_CLE,
  FULL_OP_CNGT,
};

enum InstructionType {
  TYPE_IMMEDIATE,
  TYPE_JUMP,
  TYPE_REGISTER,
  TYPE_COPROCESSOR,
  TYPE_REGISTER_IMMEDIATE,
  TYPE_CACHE,
  TYPE_NOOP,
};

// Across all instruction types
enum OpCode {
  OP_SPECIAL = 0b000000,
  OP_REGIMM = 0b000001,
  OP_ADDI = 0b001000,
  OP_ADDIU = 0b001001,
  OP_ANDI = 0b001100,
  OP_COPZ = 0b010000, // Last two bits determine coprocessor number
  OP_COP0 = 0b010000,
  OP_COP1 = 0b010001,
  OP_COP2 = 0b010010,
  OP_COP3 = 0b010011,
  OP_BEQ = 0b000100,
  OP_BEQL = 0b010100,
  OP_BGTZ = 0b000111,
  OP_BGTZL = 0b010111,
  OP_BLEZ = 0b000110,
  OP_BLEZL = 0b010110,
  OP_BNE = 0b000101,
  OP_BNEL = 0b010101,
  OP_CACHE = 0b101111,
  OP_DADDI = 0b011000,
  OP_DADDIU = 0b011001,
  OP_JUMP = 0b000010,
  OP_JAL = 0b000011,
  OP_LB = 0b100000,
  OP_LBU = 0b100100,
  OP_LD = 0b110111,
  OP_LDCZ = 0b110100, // Last two bits determine coprocessor number
  OP_LDC0 = 0b110100,
  OP_LDC1 = 0b110101,
  OP_LDC2 = 0b110110,
  OP_LDL = 0b011010,
  OP_LH = 0b100001,
  OP_LHU = 0b100101,
  OP_LL = 0b110000,
  OP_LLD = 0b110100,
  OP_LUI = 0b001111,
  OP_LW = 0b100011,
  OP_LWCZ = 0b110000, // Last two bits determine coprocessor number
  OP_LWC0 = 0b110000,
  OP_LWC1 = 0b110001,
  OP_LWC2 = 0b110010,
  OP_LWL = 0b100010,
  OP_LWR = 0b100110,
  OP_LWU = 0b100111,
  OP_ORI = 0b001101,
  OP_SB = 0b101000,
  OP_SC = 0b111000,
  OP_SCD = 0b111100,
  OP_SD = 0b111111,
  OP_SDCZ = 0b111100, // Last two bits determine coprocessor number
  OP_SDC0 = 0b111100,
  OP_SDC1 = 0b111101,
  OP_SDC2 = 0b111110,
  OP_SDL = 0b101100,
  OP_SDR = 0b101101,
  OP_SH = 0b101001,
  OP_SLTI = 0b001010,
  OP_SLTIU = 0b001011,
  OP_SW = 0b101011,
  OP_SWCZ = 0b111000, // Last two bits determine coprocessor number
  OP_SWC0 = 0b111000,
  OP_SWC1 = 0b111001,
  OP_SWC2 = 0b111010,
  OP_SWL = 0b101010,
  OP_SWR = 0b101110,
  OP_XORI = 0b001110,
};

// R-type
enum FuncCode {
  FUNC_ADD = 0b100000,
  FUNC_ADDU = 0b100001,
  FUNC_AND = 0b100100,
  FUNC_BREAK = 0b001101,
  FUNC_DADD = 0b101100,
  FUNC_DADDU = 0b101101,
  FUNC_DDIV = 0b011110,
  FUNC_DDIVU = 0b011111,
  FUNC_DIV = 0b011010,
  FUNC_DIVU = 0b011011,
  FUNC_DMULT = 0b011100,
  FUNC_DMULTU = 0b011101,
  FUNC_DSLL = 0b111000,
  FUNC_DSLLV = 0b010100,
  FUNC_DSLL32 = 0b111100,
  FUNC_DSRA = 0b111011,
  FUNC_DSRAV = 0b010111,
  FUNC_DSRA32 = 0b111111,
  FUNC_DSRL = 0b111010,
  FUNC_DSRLV = 0b010110,
  FUNC_DSLR32 = 0b111110,
  FUNC_DSUB = 0b101110,
  FUNC_DSUBU = 0b101111,
  FUNC_ERET = 0b011000, // TODO: Should this be in here?
  FUNC_JALR = 0b001001,
  FUNC_JR = 0b001000,
  FUNC_MFHI = 0b010000,
  FUNC_MFLO = 0b010010,
  FUNC_MTHI = 0b010001,
  FUNC_MTLO = 0b010011,
  FUNC_MULT = 0b011000,
  FUNC_MULTU = 0b011001,
  FUNC_NOR = 0b100111,
  FUNC_OR = 0b100101,
  FUNC_SLL = 0b000000,
  FUNC_SLLV = 0b000100,
  FUNC_SLT = 0b101010,
  FUNC_SLTU = 0b101011,
  FUNC_SRA = 0b000011,
  FUNC_SRAV = 0b000111,
  FUNC_SRL = 0b000010,
  FUNC_SRLV = 0b000110,
  FUNC_SUB = 0b100010,
  FUNC_SUBU = 0b100011,
  FUNC_SYNC = 0b001111,
  FUNC_SYSCALL = 0b001100,
  FUNC_TEQ = 0b110100,
  FUNC_TGE = 0b110000,
  FUNC_TGEU = 0b110001,
  FUNC_TLBP = 0b001000,  // TODO: Should this be in here?
  FUNC_TLBR = 0b000001,  // TODO: Should this be in here?
  FUNC_TLBWI = 0b000010, // TODO: Should this be in here?
  FUNC_TLBWR = 0b000110,
  FUNC_TLT = 0b110010,
  FUNC_TLTU = 0b110011,
  FUNC_TNE = 0b110110,
  FUNC_XOR = 0b100110,
};

// Coprocessor Sub-opcodes
enum CoprocessorOp {
  COP_BC = 0b01000,
  COP_CF = 0b00010,
  COP_CO = 0b10000,
  COP_CT = 0b00110,
  COP_DMF = 0b00001,
  COP_DMT = 0b00101,
  COP_MF = 0b00000,
  COP_MT = 0b00100,
};
enum CoprocessorSubOp {
  COP_OP_BCF = 0b00000,
  COP_OP_BCFL = 0b00010,
  COP_OP_BCT = 0b00001,
  COP_OP_BCTL = 0b00011,
};

// Branch Condition
enum BranchCondition {
  BRANCH_FALSE = 0b00000,
  BRANCH_TRUE = 0b00001,
  BRANCH_FALSE_LIKELY = 0b00010,
  BRANCH_TRUE_LIKELY = 0b00011,
};

// REGIMM Op, determine op from rt field with the following:
enum RegImmOp {
  REGIMM_OP_BLTZ = 0b00000,
  REGIMM_OP_BGEZ = 0b00001,
  REGIMM_OP_BLTZAL = 0b10000,
  REGIMM_OP_BGEZAL = 0b10001,
  REGIMM_OP_BGEZALL = 0b10011,
  REGIMM_OP_BGEZL = 0b00011,
  REGIMM_OP_BLTZALL = 0b10010,
  REGIMM_OP_BLTZL = 0b00010,
  REGIMM_OP_TEQI = 0b01100,
  REGIMM_OP_TGEI = 0b01000,
  REGIMM_OP_TGEIU = 0b01001,
  REGIMM_OP_TLTI = 0b01010,
  REGIMM_OP_TLTIU = 0b01011,
  REGIMM_OP_TNEI = 0b01110,
};

enum CacheOp {
  CACHE_OP_INDEX_INVALIDATE = 0b000'00,
  CACHE_OP_INDEX_WRITE_BACK_INVALIDATE = 0b000'01,
  CACHE_OP_INDEX_LOAD_TAG_INSTRUCTION_CACHE = 0b001'00,
  CACHE_OP_INDEX_LOAD_TAG_DATA_CACHE = 0b001'01,
  CACHE_OP_INDEX_STORE_TAG_INSTRUCTION_CACHE = 0b010'00,
  CACHE_OP_INDEX_STORE_TAG_DATA_CACHE = 0b010'01,
  CACHE_OP_CREATE_DIRTY_EXCLUSIVE = 0b011'01,
  CACHE_OP_HIT_INVALIDATE_INSTRUCTION_CACHE = 0b100'00,
  CACHE_OP_HIT_INVALIDATE_DATA_CACHE = 0b100'01,
  CACHE_OP_HIT_WRITE_BACK_INVALIDATE = 0b101'01,
  CACHE_OP_FILL = 0b101'00,
  CACHE_OP_HIT_WRITE_BACK_INSTRUCTION_CACHE = 0b110'00,
  CACHE_OP_HIT_WRITE_BACK_DATA_CACHE = 0b110'01,
};

enum FPUFormat {
  FMT_SINGLE = 16,
  FMT_DOUBLE = 17,
  FMT_WORD = 20,
  FMT_LONG = 21,
};

// I-type
struct ImmediateInstruction {
  uint16_t immediate;
  u8 rt;
  u8 rs;
  OpCode op;
} __attribute__((aligned(4)));

// J-type
struct JumpInstruction {
  u32 target;
  OpCode op;
} __attribute__((aligned(4)));

// R-type
struct RegisterInstruction {
  FuncCode func;
  u8 sa;
  u8 rd;
  u8 rt;
  u8 rs;
  OpCode op;
} __attribute__((aligned(4)));

// RegImm-type
struct RegisterImmediateInstruction {
  uint16_t immediate;
  RegImmOp rt;
  u8 rs;
  OpCode op;
} __attribute__((aligned(4)));

// Coprocessor-type
enum CoprocessorType {
  COP_TYPE_OP_NO_REGISTER,
  COP_TYPE_OP_REGISTER,
  COP_TYPE_COFUNC,
  COP_TYPE_FPU,
  COP_TYPE_INVALID,
};

struct CoprocessorCoFuncInstruction {
  u32 data;
  bool unused;
  OpCode op;
} __attribute__((aligned(4)));

struct CoprocessorOpNoRegisterInstruction {
  uint16_t immediate;
  CoprocessorSubOp sub_op;
  CoprocessorOp cop_op;
  OpCode op;
} __attribute__((aligned(4)));

struct CoprocessorOpRegisterInstruction {
  uint16_t unused;
  u8 rd;
  u8 rt;
  CoprocessorOp cop_op;
  OpCode op;
} __attribute__((aligned(4)));

struct CoprocessorFPUInstruction {
  u8 func;
  u8 fd;
  u8 fs;
  u8 ft;
  FPUFormat fmt;
  OpCode op;
} __attribute__((aligned(4)));

struct CoprocessorInstruction {
  CoprocessorType type;
  union {
    CoprocessorCoFuncInstruction cop_co_func;
    CoprocessorOpNoRegisterInstruction cop_op_no_register;
    CoprocessorOpRegisterInstruction cop_op_register;
    CoprocessorFPUInstruction cop_fpu;
  };
} __attribute__((aligned(4)));

// Cache operation
struct CacheInstruction {
  uint16_t offset;
  CacheOp cache_op;
  u8 base;
  OpCode op;
} __attribute__((aligned(4)));

// Base instruction type
struct Instruction {
  InstructionType type;
  FullOp full_op;
  union {
    ImmediateInstruction immediate;
    JumpInstruction jump;
    RegisterInstruction reg;
    RegisterImmediateInstruction regimm;
    CoprocessorInstruction coprocessor;
    CacheInstruction cache;
  };
};

// Helper functions to extract fields from instructions
inline uint16_t get_immediate(u32 raw) { return raw & 0xFFFF; }
inline u8 get_rt(u32 raw) { return (raw >> 16) & 0x1F; }
inline u8 get_rs(u32 raw) { return (raw >> 21) & 0x1F; }
inline OpCode get_op(u32 raw) {
  return static_cast<OpCode>((raw >> 26) & 0x3F);
}
inline u32 get_target(u32 raw) { return raw & 0x3FFFFFF; }
inline u8 get_rd(u32 raw) { return (raw >> 11) & 0x1F; }
inline u8 get_sa(u32 raw) { return (raw >> 6) & 0x1F; }
inline FuncCode get_func(u32 raw) {
  return static_cast<FuncCode>(raw & 0x3F);
}
inline RegImmOp get_regimm_rt(u32 raw) {
  return static_cast<RegImmOp>((raw >> 16) & 0x1F);
}
inline CoprocessorOp get_cop_op(u32 raw) {
  return static_cast<CoprocessorOp>((raw >> 21) & 0x1F);
}
inline CoprocessorSubOp get_cop_sub_op(u32 raw) {
  return static_cast<CoprocessorSubOp>((raw >> 16) & 0x1F);
}
inline FPUFormat get_fmt(u32 raw) {
  return static_cast<FPUFormat>((raw >> 21) & 0x1F);
}
inline u8 get_ft(u32 raw) { return (raw >> 16) & 0x1F; }
inline u8 get_fs(u32 raw) { return (raw >> 11) & 0x1F; }
inline u8 get_fd(u32 raw) { return (raw >> 6) & 0x1F; }
inline u8 get_fpu_func(u32 raw) { return raw & 0x3F; }
inline u8 get_base(u32 raw) { return (raw >> 21) & 0x1F; }
inline CacheOp get_cache_op(u32 raw) {
  return static_cast<CacheOp>((raw >> 16) & 0x1F);
}
inline uint16_t get_offset(u32 raw) { return raw & 0xFFFF; }

// Helper functions to populate instruction structs using bitwise operations
inline void populate_immediate_instruction(ImmediateInstruction *inst,
                                           u32 raw) {
  inst->immediate = get_immediate(raw);
  inst->rt = get_rt(raw);
  inst->rs = get_rs(raw);
  inst->op = get_op(raw);
}

inline void populate_jump_instruction(JumpInstruction *inst, u32 raw) {
  inst->target = get_target(raw);
  inst->op = get_op(raw);
}

inline void populate_register_instruction(RegisterInstruction *inst,
                                          u32 raw) {
  inst->func = get_func(raw);
  inst->sa = get_sa(raw);
  inst->rd = get_rd(raw);
  inst->rt = get_rt(raw);
  inst->rs = get_rs(raw);
  inst->op = get_op(raw);
}

inline void
populate_register_immediate_instruction(RegisterImmediateInstruction *inst,
                                        u32 raw) {
  inst->immediate = get_immediate(raw);
  inst->rt = get_regimm_rt(raw);
  inst->rs = get_rs(raw);
  inst->op = get_op(raw);
}

inline void
populate_coprocessor_co_func_instruction(CoprocessorCoFuncInstruction *inst,
                                         u32 raw) {
  inst->data = raw & 0x1FFFFFF;
  inst->unused = (raw >> 25) & 0x1;
  inst->op = get_op(raw);
}

inline void populate_coprocessor_op_no_register_instruction(
    CoprocessorOpNoRegisterInstruction *inst, u32 raw) {
  inst->immediate = get_immediate(raw);
  inst->sub_op = get_cop_sub_op(raw);
  inst->cop_op = get_cop_op(raw);
  inst->op = get_op(raw);
}

inline void populate_coprocessor_op_register_instruction(
    CoprocessorOpRegisterInstruction *inst, u32 raw) {
  inst->unused = raw & 0x7FF;
  inst->rd = get_rd(raw);
  inst->rt = get_rt(raw);
  inst->cop_op = get_cop_op(raw);
  inst->op = get_op(raw);
}

inline void
populate_coprocessor_fpu_instruction(CoprocessorFPUInstruction *inst,
                                     u32 raw) {
  inst->func = get_fpu_func(raw);
  inst->fd = get_fd(raw);
  inst->fs = get_fs(raw);
  inst->ft = get_ft(raw);
  inst->fmt = get_fmt(raw);
  inst->op = get_op(raw);
}

inline void populate_cache_instruction(CacheInstruction *inst, u32 raw) {
  inst->offset = get_offset(raw);
  inst->cache_op = get_cache_op(raw);
  inst->base = get_base(raw);
  inst->op = get_op(raw);
}

Instruction mips_decode(u32 instruction);
