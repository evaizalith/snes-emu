#include <iostream>
#include <cassert>
#include <vector>
#include "../cpu/5A22.hpp"

using std::vector;

int main() {
    _5A22 cpu;

    {
        vector<uint8_t> program;
        program.push_back(0xA9); // LDA 
        program.push_back(0xAA); // immediate

        cpu.load_memory(program);

        cpu.step();

        auto reg = cpu.dump_registers();
        assert(reg.A == 0xAA);
    }

    std::cout << "Passed all CPU tests" << std::endl;

    return 0;
}
