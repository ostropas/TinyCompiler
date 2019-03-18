#include "Compiler.h"

void Compiler::Gen(Command command)
{
    _programm.emplace_back(command);
    ++_pc;
}

vector<Command> Compiler::Ñompile(shared_ptr<Node> node)
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
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IADD)));
        break;
    case ParserKind::SUB:
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ISUB)));
        break;
    case ParserKind::LT:
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ILT)));
        break;
    case ParserKind::SET:
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::ISTORE)));
        Gen(static_cast<Command>(Command(node->op1->value)));
        break;
    case ParserKind::IF1:
        Ñompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr = _pc;
        Gen(static_cast<Command>(Command(0)));
        Ñompile(node->op2);
        _programm[addr] = _pc;
        break;
    case ParserKind::IF2:
        Ñompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr1 = _pc;
        Gen(static_cast<Command>(Command(0)));

        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        addr2 = _pc;
        Gen(static_cast<Command>(Command(0)));

        _programm[addr1] = Command(_pc);
        Ñompile(node->op3);
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::WHILE:
        addr1 = _pc;
        Ñompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr2 = _pc;
        Gen(static_cast<Command>(Command(0)));
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        Gen(static_cast<Command>(Command(static_cast<int>(addr1))));
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::DO:
        addr = _pc;
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::JNZ)));
        Gen(static_cast<Command>(Command(static_cast<int>(addr))));
        break;
    case ParserKind::SEQ:
        Ñompile(node->op1);
        Ñompile(node->op2);
        break;
    case ParserKind::EXPR:
        Ñompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::IPOP)));
        break;
    case ParserKind::PROG:
        Ñompile(node->op1);
        Gen(static_cast<Command>(Command(VirtualMachineInstructions::HALT)));
        break;
    }
    return _programm;
}
