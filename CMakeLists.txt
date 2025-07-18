cmake_minimum_required(VERSION 3.10)
project(RISCV_Simulator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simulator
    src/main.cpp
    src/cpu.cpp
    src/memory.cpp
    src/registers.cpp
    # 注意：我们暂时不编译 instructions/base.cpp，因为它是空的
)

target_include_directories(simulator PRIVATE
    include
    external/elfio
)
