#include "registers.h"
#include <iostream>
#include <iomanip>

Registers::Registers() : pc(0) {
    x.fill(0); // 所有寄存器初始化为 0
}

void Registers::dump() const {
    std::cout << "--- Register Dump ---" << std::endl;
    for (size_t i = 0; i < 32; ++i) {
        std::cout << "x" << i << ": 0x" << std::hex << std::setw(8) << std::setfill('0') << x[i] << "  ";
        if ((i + 1) % 4 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << "PC: 0x" << std::hex << std::setw(8) << std::setfill('0') << pc << std::endl;
    std::cout << "--------------------" << std::endl;
}
