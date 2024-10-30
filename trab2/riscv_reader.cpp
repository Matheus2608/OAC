#include "riscv_reader.hpp"
#include <iostream>
#include <fstream>

using namespace std;

const string code_file_name = "code.bin";
const string data_file_name = "data.bin";

uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000;
uint32_t sp = 0x00003ffc;
uint32_t gp = 0x00001800;

vector<uint8_t> readInstructions(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return vector<uint8_t>();
    }

    uint8_t byte;
    vector<uint8_t> instructions;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        instructions.push_back(byte);
    }

    file.close();

    return instructions;
}

void printInstructions(vector<uint8_t> instructions) {
    for (size_t i = 0; i < instructions.size(); ++i) {
        cout << "Byte " << i << ": " << hex << static_cast<int>(instructions[i]) << endl;
    }
}

int main() {

    vector<uint8_t> instructions = readInstructions(code_file_name);
    vector<uint8_t> data = readInstructions(data_file_name);
    // printInstructions(instructions);
    cout << "Byte 4 = "  << hex << static_cast<int>(data[4]) << endl;
    //printInstructions(data);
    return 0;
}
