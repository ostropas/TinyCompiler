#pragma once
#include <utility>
#include <vector>

#include "../Parser/NodeStruct.h"
#include "Instructions.h"

using namespace std;

class Compiler {
public:
    void gen(Command command);
    vector<Command> compile(shared_ptr<Node> node);

private:
    int _pc = 0;
    vector<Command> _programm = vector<Command>();
};
