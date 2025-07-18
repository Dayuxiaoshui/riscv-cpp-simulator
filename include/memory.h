// include/memory.h
#pragma once
#include <vector>
#include <cstdint>

class Memory {
public: // 注意，这里改为 public
    std::vector<uint8_t> ram; 

public:
    Memory(size_t size);
    void load(uint32_t addr, const char* data, size_t len);
};
