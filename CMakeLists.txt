cmake_minimum_required(VERSION 3.10)
project(neo64)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
  src/mips/decoder.cpp
  src/mips/disassembler.cpp
  src/mips/test.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)
