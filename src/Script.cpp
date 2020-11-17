#include "Script.h"
#include <fstream>
#include <string>

Script::Script()
{
    std::ifstream fileStream("script.lua");
    auto scriptContents = std::string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    luaState.open_libraries(
        sol::lib::base,
		sol::lib::string,
		sol::lib::math,
		sol::lib::table,
		sol::lib::io);
    luaState.safe_script(scriptContents);

    luaState["SetAnimateTime"] = [this](int time){
        this->animateTime = time;
    };
}

void Script::ParseOptions(gameoptions* opt)
{
    auto options = luaState["options"];
    if(options)
    {
        auto enable_colour = luaState["options"]["enable_colour"];
        if(enable_colour.get_type() == sol::type::boolean)
        {
            opt->enable_color = enable_colour;
        }
        auto animate = luaState["options"]["animate"];
        if(animate.get_type() == sol::type::boolean)
        {
            opt->animate = animate;
        }
        auto interactive = luaState["options"]["interactive"];
        if(interactive.get_type() == sol::type::boolean)
        {
            opt->interactive = interactive;
        }
        auto ai = luaState["options"]["ai"];
        if(ai.get_type() == sol::type::boolean)
        {
            opt->ai = ai;
        }
        auto grid_height = luaState["options"]["grid_height"];
        if(grid_height.get_type() == sol::type::number)
        {
            opt->grid_height = grid_height;
        }
        auto grid_width = luaState["options"]["grid_width"];
        if(grid_width.get_type() == sol::type::number)
        {
            opt->grid_width = grid_width;
        }
        auto spawn_rate = luaState["options"]["spawn_rate"];
        if(spawn_rate.get_type() == sol::type::number)
        {
            opt->spawn_rate = spawn_rate;
        }
    } 
}

void Script::OnGameLoopIteration()
{
    sol::function callableFunc = luaState["onGameLoopIteration"];
    std::function<void()> func = callableFunc; 
    func();
}

int Script::GetAnimateTime()
{
    return animateTime;
}