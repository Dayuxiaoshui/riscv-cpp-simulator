#pragma once
#include <array>
#include <cstdint>

class Registers {
public:
    Registers();
    void dump() const; // 用于调试，打印所有寄存器状态

    // 标量整数寄存器 x0-x31
    std::array<uint32_t, 32> x;
    // 程序计数器
    uint32_t pc;

    // TODO: 未来在这里添加向量寄存器
};
