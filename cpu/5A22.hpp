#ifndef EVA_SNESEMU_CPU_5A22
#define EVA_SNESEMU_CPU_5A22

#include <cstdint>
#include <vector>

using std::vector;

struct _5A22_registers {
    // General Registers
    uint8_t A; // A, X, Y are 8-bit temporarily. Need to be expanded for 16 bit and non-emulation support
    uint8_t X;
    uint8_t Y;
    uint16_t PC;
    uint16_t S;
    uint8_t P;
    uint16_t D;
    uint8_t DB;
    uint8_t PB;

    // Flags / Processor Status Registers
    bool carry;
    bool zero;
    bool irq;
    bool decimal;
    bool breakflag;
    bool unused;
    bool overflow;
    bool sign;
    //bool emulation; 
};

class _5A22 {
public:
    _5A22(int _RAMsize = 128);           //!< Accepts number of kilobytes to allocate as an argument. The SNES has 128 kilobytes of RAM
    ~_5A22();

    void step();                         //!< Read and execute next instruction; increment PC
                                        
    void load_memory(vector<uint8_t>);   //!< Writes a passed vector to the RAM
    

    _5A22_registers dump_registers();   //!< Provides a copy of register contents for debugging
    vector<uint8_t> dump_memory();      //!< Provides a vector containing a copy of RAM

private:
    _5A22_registers reg;
    uint8_t* RAM;
    int RAMsize;
};

#endif
