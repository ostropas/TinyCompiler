#pragma once
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class VirtualMachineInstructions {
    NONE = -1,
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

typedef pair<VirtualMachineInstructions, int> Command;

class VirtualMachine {
public:
    static void Run(vector<Command> programm);
};
