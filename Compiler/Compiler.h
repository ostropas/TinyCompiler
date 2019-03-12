#pragma once
#include "../VirtualMachine/VirtualMachine.h"
#include "../Parser/Parser.h"

#include <vector>
#include <utility>

using namespace std;

class Compiler {
public:
    void Gen(Command command);
    vector<Command> Ñompile(shared_ptr<Node> node);

private:
    size_t _pc = 0;
    vector<Command> _programm = vector<Command>();
};
