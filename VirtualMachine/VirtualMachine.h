#pragma once
#include "../Compiler/Compiler.h"
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class VirtualMachine {
public:
    static void Run(vector<Command> programm);
};
