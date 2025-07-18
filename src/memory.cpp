#include "memory.h"
#include <cstring> // for memcpy

Memory::Memory(size_t size) {
    ram.resize(size, 0); // 分配内存并初始化为 0
}

void Memory::load(uint32_t addr, const char* data, size_t len) {
    if (addr + len > ram.size()) {
        // 实际项目中应处理错误，这里简化
        return;
    }
    memcpy(ram.data() + addr, data, len);
}
