#include "5A22.hpp"
#include <stdexcept>
#include <sstream>

_5A22::_5A22(int _RAMsize) {
    RAMsize = _RAMsize * 1024;
    RAM = new uint8_t[RAMsize];
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
    if (size > RAMsize) {
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
        copy.push_back(RAM[i]);
    }

    return copy;
}

// This function just ensures that we never request memory from an illegal address
uint8_t _5A22::read_mem(uint32_t addr) {
    return RAM[addr % (RAMsize)];
}

// Likewise, we never write in an illegal address 
void _5A22::write_mem(uint32_t addr, uint8_t data) {
    RAM[addr % (RAMsize)] = data;
}

uint8_t _5A22::pc_next() {
    uint32_t addr = (reg.PB << 16) | reg.PC; // Adds program counter bank to program counter
    ++reg.PC;
    return read_mem(addr);
}

void _5A22::step() {
    uint8_t opcode = pc_next(); 

    switch (opcode) {
        case 0xA9: { // LDA #const immediate 
            uint8_t imm = pc_next();
            reg.A = imm;
            break;
        }
        case 0xAD: { // LDA addr
            break;
        }
        case 0xAF: { // LDA long
            break;
        }
        case 0x81: { // STA dp indexed indirect X
            break;
        }
        case 0x85: { // STA dp
            break;
        }
        default:
            throw std::runtime_error("Unknown opcode " + std::to_string(opcode));
            break;
    }

}


