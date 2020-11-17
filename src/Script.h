#pragma once

#include "options.h"
#include "sol/sol.hpp"
#include "engine.h"

class Script
{
public:
    Script(gamestate*);
    void ParseOptions(gameoptions* opt);
    void OnGameLoopIteration();
    void OnGameLoopIterationComplete();
    int GetAnimateTime();
    const std::string& GetMessage();
private:
    gamestate* state;
    sol::state luaState;
    int animateTime = 160;
    std::string message;
};