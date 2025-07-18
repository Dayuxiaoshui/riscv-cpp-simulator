// include/cpu.h
#pragma once
#include "memory.h"
#include "registers.h"

class CPU {
public:
    CPU(Memory& mem, Registers& regs);
    void run(); 
    
    void set_pc(uint32_t val) { regs_.pc = val; }
    uint32_t get_pc() const { return regs_.pc; }

private:
    uint32_t fetch();
    void decode_and_execute(uint32_t instruction);

    Memory& mem_;
    Registers& regs_;
    bool halted_; // 用于控制循环结束
};
