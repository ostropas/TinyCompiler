#pragma once
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../Compiler/Instructions.h"

using namespace std;

class VirtualMachine {
public:
    static void run(vector<Command> programm);
};
