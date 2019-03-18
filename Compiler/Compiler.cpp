#include "Compiler.h"

void Compiler::Gen(Command command)
{
    _programm.emplace_back(command);
    ++_pc;
}

vector<Command> Compiler::�ompile(shared_ptr<Node> node)
{
    size_t addr, addr1, addr2;

    switch (node->kind) {
    case ParserKind::VAR:
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IFETCH)));
        Gen(static_cast<Command>(Command(node->value)));
        break;
    case ParserKind::CONST:
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IPUSH)));
        Gen(static_cast<Command>(Command(node->value)));
        break;
    case ParserKind::ADD:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IADD)));
        break;
    case ParserKind::SUB:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ISUB)));
        break;
    case ParserKind::LT:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ILT)));
        break;
    case ParserKind::SET:
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ISTORE)));
        Gen(static_cast<Command>(Command(node->op1->value)));
        break;
    case ParserKind::IF1:
        �ompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr = _pc;
        Gen(static_cast<Command>(Command(0)));
        �ompile(node->op2);
        _programm[addr] = _pc;
        break;
    case ParserKind::IF2:
        �ompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr1 = _pc;
        Gen(static_cast<Command>(Command(0)));

        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        addr2 = _pc;
        Gen(static_cast<Command>(Command(0)));

        _programm[addr1] = Command(_pc);
        �ompile(node->op3);
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::WHILE:
        addr1 = _pc;
        �ompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr2 = _pc;
        Gen(static_cast<Command>(Command(0)));
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        Gen(static_cast<Command>(Command(static_cast<int>(addr1))));
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::DO:
        addr = _pc;
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JNZ)));
        Gen(static_cast<Command>(Command(static_cast<int>(addr))));
        break;
    case ParserKind::SEQ:
        �ompile(node->op1);
        �ompile(node->op2);
        break;
    case ParserKind::EXPR:
        �ompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IPOP)));
        break;
    case ParserKind::PROG:
        �ompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::HALT)));
        break;
    }
    return _programm;
}
