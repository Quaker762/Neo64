#include <fstream>
#include <iostream>
#include <stdexcept>

#include "decoder.h"
#include "disassembler.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <bios_file>" << std::endl;
    return 1;
  }

  std::ifstream bios(argv[1], std::ios::binary);
  if (!bios) {
    std::cerr << "Failed to open BIOS file" << std::endl;
    return 1;
  }

  long long int location = 0;
  while (bios.good()) {
    uint32_t instruction;
    if (!bios.read(reinterpret_cast<char *>(&instruction),
                   sizeof(instruction))) {
      break;
    }

    try {
      // MIPS uses big endian, so swap bytes if on little endian
      instruction = __builtin_bswap32(instruction);

      Instruction decoded = mips_decode(instruction);
      std::cout << "0x" << std::hex << location << "\t" << "0x" << std::setw(8)
                << std::setfill('0') << instruction << "\t"
                << disassemble(decoded) << std::endl;
    } catch (std::runtime_error error) {
      std::cerr << "Failed to disassemble instruction." << std::endl;
    }
    location += 4;
  }
  return 0;
}
