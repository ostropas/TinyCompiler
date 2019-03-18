#pragma once
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

struct Command {
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