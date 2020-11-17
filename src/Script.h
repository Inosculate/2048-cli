#pragma once

#include "options.h"
#include "sol/sol.hpp"

class Script
{
public:
    Script();
    void ParseOptions(gameoptions* opt);
private:
    sol::state luaState;
};