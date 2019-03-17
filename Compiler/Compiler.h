#pragma once
#include "../Parser/Parser.h"

#include <utility>
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

class Command {
public:
    Command(int value)
    {
        _value = value;
    }

    Command(VirtualMachineInstructions instruction)
    {
        _value = static_cast<int>(instruction);
    }

    int GetValue()
    {
        return _value;
    }

    VirtualMachineInstructions GetInstruction()
    {
        return static_cast<VirtualMachineInstructions>(_value);
    }

private:
    int _value;
};

class Compiler {
public:
    void Gen(Command command);
    vector<Command> Ñompile(shared_ptr<Node> node);

private:
    int _pc = 0;
    vector<Command> _programm = vector<Command>();
};
