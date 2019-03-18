#include "VirtualMachine.h"

void VirtualMachine::run(vector<Command> programm)
{
    array<int, 26> var = {};
    for (int i = 0; i < 26; i++) {
        var[i] = 0;
    }
    vector<int> stack;
    size_t pc = 0;
    for (;;) {
        auto op = programm[pc].GetInstruction();
        int arg = NULL;

        if (pc < programm.size() - 1) {
            arg = programm[pc + 1].GetValue();
        }

        switch (op) {
        case VirtualMachineInstructions::IFETCH:
            stack.push_back(var[arg]);
            pc += 2;
            continue;
        case VirtualMachineInstructions::ISTORE:
            var[arg] = stack[stack.size() - 1];
            stack.pop_back();
            pc += 2;
            continue;
        case VirtualMachineInstructions::IPUSH:
            stack.push_back(arg);
            pc += 2;
            continue;
        case VirtualMachineInstructions::IPOP:
            stack.push_back(arg);
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::IADD:
            stack[stack.size() - 2] += stack[stack.size() - 2];
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::ISUB:
            stack[stack.size() - 2] -= stack[stack.size() - 2];
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::ILT:
            if (stack[stack.size() - 2] < stack[stack.size() - 1]) {
                stack[stack.size() - 2] = 1;
            } else {
                stack[stack.size() - 2] = 0;
            }
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::JZ:
            if (stack[stack.size() - 1] == 0) {
                pc = arg;
            } else {
                pc += 2;
            }
            stack.pop_back();
            continue;
        case VirtualMachineInstructions::JNZ:
            if (stack[stack.size() - 1] != 0) {
                pc = arg;
            } else {
                pc += 2;
            }
            stack.pop_back();
            continue;
        case VirtualMachineInstructions::JMP:
            pc = arg;
            continue;
        case VirtualMachineInstructions::HALT:
            break;
        }
        break;
    }

    cout << "Execution finished.\n";

    for (size_t i = 0; i < 26; i++) {
        cout << static_cast<char>(i + static_cast<int>('a')) << " = " << var[i] << '\n';
    }
}
