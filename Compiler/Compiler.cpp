#include "Compiler.h"

void Compiler::Gen(Command command)
{
    _programm.emplace_back(command);
    ++_pc;
}

vector<Command> Compiler::�ompile(shared_ptr<Node> node)
{
    switch (node->kind) {
    case ParserKind::VAR:
        Gen(make_pair(VirtualMachineInstructions::IFETCH, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::CONST:
        Gen(make_pair(VirtualMachineInstructions::IPUSH, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::ADD:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::IADD, 0));
        break;
    case ParserKind::SUB:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ISUB, 0));
        break;
    case ParserKind::LT:
        �ompile(node->op1);
        �ompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ILT, 0));
        break;
    case ParserKind::SET:
        �ompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ISTORE, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::IF1:
        break;
    case ParserKind::IF2:
        break;
    case ParserKind::WHILE:
        break;
    case ParserKind::DO:
        break;
    case ParserKind::SEQ:
        break;
    case ParserKind::EXPR:
        break;
    case ParserKind::PROG:
        break;
    }
    return _programm;
}
