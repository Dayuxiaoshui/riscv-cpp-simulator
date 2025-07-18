// src/cpu.cpp
#include "cpu.h"
#include <iostream>
#include <iomanip>

CPU::CPU(Memory& mem, Registers& regs) : mem_(mem), regs_(regs), halted_(false) {}

uint32_t CPU::fetch() {
    // 从 PC 指向的内存地址读取一条 32 位指令
    uint32_t instruction = *(uint32_t*)(mem_.ram.data() + regs_.pc);
    // PC 前进 4 个字节，指向下一条指令
    regs_.pc += 4; 
    return instruction;
}

void CPU::decode_and_execute(uint32_t instruction) {
    uint32_t opcode = instruction & 0x7F; // 提取 opcode

    // 判断指令类型并执行
    if (opcode == 0x13) { // ADDI 指令
        uint32_t rd = (instruction >> 7) & 0x1F;
        uint32_t rs1 = (instruction >> 15) & 0x1F;
        // 立即数需要进行符号扩展
        int32_t imm = (int32_t)(instruction & 0xFFF00000) >> 20; 

        std::cout << "Executing ADDI: x" << rd << " = x" << rs1 << " + " << imm << std::endl;
        regs_.x[rd] = regs_.x[rs1] + imm;

    } else if (instruction == 0x00100073) { // EBREAK 指令
        std::cout << "EBREAK encountered. Halting." << std::endl;
        halted_ = true;
    } else {
        std::cout << "Unknown instruction: 0x" << std::hex << instruction << std::endl;
        halted_ = true;
    }
}

void CPU::run() {
    std::cout << "CPU run loop started." << std::endl;
    while (!halted_) {
        // 确保 x0 寄存器在每次循环开始时都为 0
        regs_.x[0] = 0;

        uint32_t instruction = fetch();
        
        if (halted_) break; // 如果 fetch 过程中发生错误（未来可能）

        decode_and_execute(instruction);

        // 每次执行完一条指令后，打印寄存器状态，方便我们观察
        regs_.dump();
    }
    std::cout << "CPU run loop finished." << std::endl;
}
