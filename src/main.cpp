#include <iostream>
#include <elfio/elfio.hpp>
#include "cpu.h"
#include "memory.h"
#include "registers.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    ELFIO::elfio reader;
    if (!reader.load(argv[1])) {
        std::cerr << "Failed to load ELF file: " << argv[1] << std::endl;
        return 1;
    }

    // 1. 初始化组件
    Memory mem(1024 * 1024); // 1MB RAM
    Registers regs;
    CPU cpu(mem, regs);

    // 2. 加载 ELF 文件到内存
    std::cout << "Loading ELF segments..." << std::endl;
    for (const auto& seg : reader.segments) {
        if (seg->get_type() == ELFIO::PT_LOAD) {
            // 新的、正确的代码
            mem.load(seg->get_virtual_address(), seg->get_data(), seg->get_memory_size());

        }
    }
    std::cout << "ELF loaded." << std::endl;

    // 3. 设置程序入口点
    cpu.set_pc(reader.get_entry());
    std::cout << "PC set to entry point: 0x" << std::hex << cpu.get_pc() << std::endl;

    // 4. 运行前打印初始状态（用于调试）
    regs.dump();
    
    // 5. 启动 CPU (目前只会打印一条信息)
    cpu.run();

    return 0;
}
