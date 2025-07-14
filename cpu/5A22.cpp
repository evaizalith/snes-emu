#include "5A22.hpp"
#include <stdexcept>
#include <sstream>

_5A22::_5A22(int _RAMsize) {
    RAM = new uint8_t[_RAMsize * 1024];
    RAMsize = _RAMsize;
    reg.PC = 0;
    reg.S = 0;
}

_5A22::~_5A22() {
    delete[] RAM;
}

void _5A22::load_memory(vector<uint8_t> program) {
    if (program.empty()) {
        throw std::runtime_error("Program passed does not contain data");
    }

    int size = program.size();
    if (size > RAMsize * 1024) {
        throw std::runtime_error(
                (std::ostringstream() << "Program passed is too big. Expected " << RAMsize << " kilobytes, got " << size << " bytes").str());
    }

    for (int i = 0; i < size; i++) {
        RAM[i] = program[i];
    }
}

_5A22_registers _5A22::dump_registers() {
    return reg;
}

vector<uint8_t> _5A22::dump_memory() {
    if (!RAM) {
        throw std::runtime_error("RAM is null; cannot return a copy"); 
    }

    vector<uint8_t> copy;
    for (int i = 0; i < RAMsize; i++) {
        copy[i] = RAM[i];
    }

    return copy;
}

void _5A22::step() {
    

}


