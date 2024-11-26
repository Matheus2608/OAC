echo "Resultado do programa 1"
echo ""
g++ riscv_reader.cpp instructions/*.cpp decoder.cpp executer.cpp memory.cpp -o out && ./out code.bin data.bin
echo ""

echo "Resultado do programa 2"
echo ""
g++ riscv_reader.cpp instructions/*.cpp decoder.cpp executer.cpp memory.cpp -o out && ./out code2.bin data2.bin
echo ""

echo "Resultado do programa 3"
echo ""
g++ riscv_reader.cpp instructions/*.cpp decoder.cpp executer.cpp memory.cpp -o out && ./out code3.bin data3.bin
echo ""
