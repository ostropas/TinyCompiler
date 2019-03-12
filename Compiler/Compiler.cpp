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
        Gen(make_pair(VirtualMachineInstructions::IFETCH, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::CONST:
        Gen(make_pair(VirtualMachineInstructions::IPUSH, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::ADD:
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::IADD, 0));
        break;
    case ParserKind::SUB:
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ISUB, 0));
        break;
    case ParserKind::LT:
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ILT, 0));
        break;
    case ParserKind::SET:
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::ISTORE, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, node->value));
        break;
    case ParserKind::IF1:
        Ñompile(node->op1);
        Gen(make_pair(VirtualMachineInstructions::JZ, 0));
        addr = _pc;
        Gen(make_pair(VirtualMachineInstructions::NONE, 0));
        Ñompile(node->op2);
        _programm[addr] = make_pair(VirtualMachineInstructions::NONE, _pc);
        break;
    case ParserKind::IF2:
        Ñompile(node->op1);
        Gen(make_pair(VirtualMachineInstructions::JZ, 0));
        addr1 = _pc;
        Gen(make_pair(VirtualMachineInstructions::NONE, 0));

        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::JMP, 0));
        addr2 = _pc;
        Gen(make_pair(VirtualMachineInstructions::NONE, 0));
        
		_programm[addr1] = make_pair(VirtualMachineInstructions::NONE, _pc);
        Ñompile(node->op3);
        _programm[addr2] = make_pair(VirtualMachineInstructions::NONE, _pc);
        break;
    case ParserKind::WHILE:
        addr1 = _pc;
        Ñompile(node->op1);
        Gen(make_pair(VirtualMachineInstructions::JZ, 0));
        addr2 = _pc;
        Gen(make_pair(VirtualMachineInstructions::NONE, 0));
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::JMP, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, addr1));
        _programm[addr2] = make_pair(VirtualMachineInstructions::NONE, _pc);
        break;
    case ParserKind::DO:
        addr = _pc;
        Ñompile(node->op1);
        Ñompile(node->op2);
        Gen(make_pair(VirtualMachineInstructions::JNZ, 0));
        Gen(make_pair(VirtualMachineInstructions::NONE, addr));
        break;
    case ParserKind::SEQ:
        Ñompile(node->op1);
        Ñompile(node->op2);
        break;
    case ParserKind::EXPR:
        Ñompile(node->op1);
        Gen(make_pair(VirtualMachineInstructions::IPOP, 0));
        break;
    case ParserKind::PROG:
        Ñompile(node->op1);
        Gen(make_pair(VirtualMachineInstructions::HALT, 0));
        break;
    }
    return _programm;
}
