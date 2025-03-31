#include <fstream>
#include <iostream>

#include "decoder.h"
#include "disassembler.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <bios_file>" << std::endl;
    return 1;
  }

  std::ifstream bios(argv[1], std::ios::binary);
  if (!bios) {
    std::cerr << "Failed to open BIOS file" << std::endl;
    return 1;
  }

  uint32_t instruction;
  if (!bios.read(reinterpret_cast<char*>(&instruction), sizeof(instruction))) {
    std::cerr << "Failed to read instruction from BIOS" << std::endl;
    return 1;
  }

  // MIPS uses big endian, so swap bytes if on little endian
  instruction = __builtin_bswap32(instruction);

  Instruction decoded = mips_decode(instruction);
  std::cout << disassemble(decoded) << std::endl;
  return 0;
}
