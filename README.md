# C++ RISC-V Simulator

一个从零开始构建的高性能RISC-V指令集模拟器，旨在支持RV32I基础指令集和RVV（向量）扩展，并探索向小型计算GPU演进的可能性。本项目注重代码的模块化、可扩展性和现代C++实践（C++20）。

## 当前状态与已实现功能

**第一阶段：基础RV32I模拟器核心功能已完成。**

*   **✅ 项目构建与结构 (Project Structure & Build):**
    *   使用 CMake 进行跨平台构建。
    *   建立了清晰、模块化的目录结构 (`src`, `include`, `tests`, `external`)。

*   **✅ 基础模拟器框架 (Core Simulator Framework):**
    *   实现了核心的 `CPU`, `Memory`, `Registers` 类。
    *   `Memory`: 能够分配指定大小的内存空间。
    *   `Registers`: 能够管理全部32个RV32I通用寄存器及程序计数器(PC)。

*   **✅ ELF 文件加载 (ELF File Loading):**
    *   成功集成 `elfio` 第三方库。
    *   能够正确解析32位RISC-V架构的ELF可执行文件。
    *   程序段(segments)被准确加载到模拟内存中，并且CPU的PC被设置到正确的程序入口点。

*   **✅ CPU 核心执行循环 (CPU Core Execution Loop):**
    *   实现了模拟器的心脏——**取指 (Fetch) -> 译码 (Decode) -> 执行 (Execute)** 的完整循环。
    *   CPU能够根据PC从内存中取出指令，并逐条执行，直到遇到特定指令（如`EBREAK`）而停机。

*   **✅ RV32I 指令集支持 (RV32I Instruction Support):**
    *   成功实现并验证了RV32I指令集中的一个关键子集：
        *   `ADDI` (立即数加法): 验证了I-Type指令的译码、立即数符号扩展和算术逻辑单元(ALU)的正确性。
        *   `EBREAK`: 用于程序调试和正常终止模拟器执行循环。

*   **✅ 调试与验证 (Debugging & Verification):**
    *   实现了寄存器状态打印 (`dump` 方法)，能够在每条指令执行后追踪CPU状态，极大地帮助了调试和验证过程。

## 安装与构建

确保您已安装 C++ 编译器 (支持C++20) 和 CMake。

```bash
# 从项目根目录运行
cmake -S . -B build && cmake --build build
```
### 使用方法

模拟器需要一个RISC-V架构的ELF文件作为输入。您可以按照以下步骤创建一个简单的测试程序并运行它。

#### 编写汇编代码
创建一个名为 `test.s` 的文件，内容如下：
```s
# test.s
.global _start

_start:
  # 测试 ADDI 指令
  addi x1, x0, 10      # x1 = x0 + 10  (x1 <- 10)
  addi x2, x1, 20      # x2 = x1 + 20  (x2 <- 30)
  addi x3, x2, -5      # x3 = x2 - 5   (x3 <- 25)
  
  # 使用 ebreak 结束程序
  ebreak
```
### 编译为ELF文件
使用RISC-V交叉编译工具链将其编译为RV32I架构的ELF文件。

```bash
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -nostdlib -o test.elf test.s
```
### 运行模拟器
```bash
./build/simulator test.elf
```
您将会看到模拟器加载程序，并逐条执行指令，同时打印每一步之后寄存器的变化情况。

## 下一步计划 (Roadmap)
我们已经有了一个坚实的基础，接下来的工作将围绕扩展指令集和提升项目质量展开。

1.  **重构指令解码器 (Refactor Instruction Decoder):**
    *   **目标：** 将当前位于 `cpu.cpp` 中的巨大 `if-else` 结构替换为更具可扩展性的设计。
    *   **方案：** 采用函数指针数组或跳转表。每条指令的实现将被移至 `src/instructions/base.cpp` 中，CPU根据指令的`opcode`进行分发调用。

2.  **完善RV32I基础指令集 (Complete RV32I Instruction Set):**
    *   按照指令类型，逐步添加并测试新的指令。
        *   **Load/Store 指令:** `LW`, `LB`, `SW`, `SB` (与内存交互)
        *   **Branch 指令:** `BEQ`, `BNE`, `BLT` (控制流)
        *   **Register-Register 指令:** `ADD`, `SUB`, `SLT`, `AND`, `OR`, `XOR`
        *   **Jump 指令:** `JAL`, `JALR`

3.  **建立自动化测试框架 (Establish a Testing Framework):**
    *   在 `tests/` 目录下集成 GoogleTest 或 Catch2 测试框架。
    *   为每条实现的指令编写单元测试，以保证其行为的正确性，并防止未来的修改破坏现有功能。

4.  **长期目标：向量扩展与GPU (Long-term Goals: Vector Extension & GPU):**
    *   在RV32I稳定后，开始研究和实现 **RVV (RISC-V Vector Extension)**。
    *   探索将模拟器扩展为一个小型计算GPU的可行性，实现SIMT（单指令多线程）等并行计算模型。

---

## 如何贡献 (Contributing)

欢迎任何形式的贡献！无论是报告Bug、提出功能建议还是提交代码。如果您希望贡献代码，请遵循以下步骤：

1.  **Fork** 本项目仓库。
2.  创建一个新的功能分支 (`git checkout -b feature/AmazingFeature`)。
3.  提交您的代码更改 (`git commit -m 'Add some AmazingFeature'`)。
4.  将您的分支推送到远程仓库 (`git push origin feature/AmazingFeature`)。
5.  创建一个 **Pull Request**。

如果您发现了问题，请在 [Issues](https://github.com/Dayuxiaoshui/riscv-cpp-simulator/issues) 页面提交一个详细的报告。

## 许可证 (License)

本项目采用 **MIT 许可证**。详细信息请参阅根目录下的 `LICENSE` 文件。

## 致谢 (Acknowledgements)

*   感谢 **RISC-V International** 提供的开放指令集标准。
*   感谢 **Serge Zaitsev** 开发了 `elfio` 库，极大地简化了ELF文件的解析工作。
*   感谢所有为开源社区做出贡献的开发者。
