#ifndef RISCV_READER_HPP
#define RISCV_READER_HPP

#include <vector>
#include <cstdint>
#include <string>

class RiscVReader {
public:
    RiscVReader(const std::string& filename);
    void readInstructions();
    void printInstructions() const;

private:
    std::string filename;
    std::vector<uint8_t> instructions; // Alterado para uint8_t
};

#endif // RISCV_READER_HPP
