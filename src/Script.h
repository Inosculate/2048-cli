#pragma once

#include "options.h"
#include "sol/sol.hpp"
#include <functional>

class Script
{
public:
    Script();
    void ParseOptions(gameoptions* opt);
    void OnGameLoopIteration();
    int GetAnimateTime();
private:
    sol::state luaState;
    int animateTime = 160;
};