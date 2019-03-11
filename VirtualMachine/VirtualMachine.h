#pragma once
#include <array>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class VirtualMachineInstructions {
    IFETCH,
    ISTORE,
    IPUSH,
    IPOP,
    IADD,
    ISUB,
    ILT,
    JZ,
    JNZ,
    JMP,
    HALT
};

class VirtualMachine {
public:
    static void Run(vector<pair<VirtualMachineInstructions, int>> programm);
};
