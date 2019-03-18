#include "Compiler.h"

void Compiler::gen(Command command)
{
    _programm.emplace_back(command);
    ++_pc;
}

vector<Command> Compiler::compile(shared_ptr<Node> node)
{
    size_t addr, addr1, addr2;

    switch (node->kind) {
    case ParserKind::VAR:
        gen(static_cast<Command>(Command(VirtualMachineInstructions::IFETCH)));
        gen(static_cast<Command>(Command(node->value)));
        break;
    case ParserKind::CONST:
        gen(static_cast<Command>(Command(VirtualMachineInstructions::IPUSH)));
        gen(static_cast<Command>(Command(node->value)));
        break;
    case ParserKind::ADD:
        compile(node->op1);
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::IADD)));
        break;
    case ParserKind::SUB:
        compile(node->op1);
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::ISUB)));
        break;
    case ParserKind::LT:
        compile(node->op1);
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::ILT)));
        break;
    case ParserKind::SET:
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::ISTORE)));
        gen(static_cast<Command>(Command(node->op1->value)));
        break;
    case ParserKind::IF1:
        compile(node->op1);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr = _pc;
        gen(static_cast<Command>(Command(0)));
        compile(node->op2);
        _programm[addr] = _pc;
        break;
    case ParserKind::IF2:
        compile(node->op1);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr1 = _pc;
        gen(static_cast<Command>(Command(0)));

        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        addr2 = _pc;
        gen(static_cast<Command>(Command(0)));

        _programm[addr1] = Command(_pc);
        compile(node->op3);
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::WHILE:
        addr1 = _pc;
        compile(node->op1);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JZ)));
        addr2 = _pc;
        gen(static_cast<Command>(Command(0)));
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JMP)));
        gen(static_cast<Command>(Command(static_cast<int>(addr1))));
        _programm[addr2] = Command(_pc);
        break;
    case ParserKind::DO:
        addr = _pc;
        compile(node->op1);
        compile(node->op2);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::JNZ)));
        gen(static_cast<Command>(Command(static_cast<int>(addr))));
        break;
    case ParserKind::SEQ:
        compile(node->op1);
        compile(node->op2);
        break;
    case ParserKind::EXPR:
        compile(node->op1);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::IPOP)));
        break;
    case ParserKind::PROG:
        compile(node->op1);
        gen(static_cast<Command>(Command(VirtualMachineInstructions::HALT)));
        break;
    }
    return _programm;
}
