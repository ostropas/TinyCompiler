#include "VirtualMachine.h"

void VirtualMachine::Run(vector<pair<VirtualMachineInstructions, int>> programm)
{
    array<int, 26> var = {};
    for (int i = 0; i < 26; i++) {
        var[i] = i;
    }
    vector<int> stack;
    size_t pc = 0;
    for (;;) {
        auto op = programm[pc].first;
        int arg = NULL;

        if (pc < programm.size()) {
            arg = programm[pc + 1].second;
        }

        switch (op) {
        case VirtualMachineInstructions::IFETCH:
            stack.push_back(var[arg]);
            pc += 2;
            continue;
        case VirtualMachineInstructions::ISTORE:
            var[arg] = stack[stack.back() - 1];
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
            stack[stack.back() - 2] += stack[stack.back() - 2];
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::ISUB:
            stack[stack.back() - 2] -= stack[stack.back() - 2];
            stack.pop_back();
            ++pc;
            continue;
        case VirtualMachineInstructions::ILT:
            if (stack[stack.back() - 2] < stack[stack.back() - 1]) {
                stack[stack.back() - 2] = 1;
            } else {
                stack[stack.back() - 2] = 0;
            }
            continue;
        case VirtualMachineInstructions::JZ:
            if (stack[stack.back() - 1] == 0) {
                pc = arg;
            } else {
                pc += 2;
            }
            stack.pop_back();
            continue;
        case VirtualMachineInstructions::JNZ:
            if (stack[stack.back() - 1] != 0) {
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
            continue;
        }
        break;
    }

    cout << "Execution finished.\n";

    for (size_t i = 0; i < 26; i++) {
        cout << static_cast<char>(i + static_cast<int>('a')) << " = " << var[i];
    }
}
