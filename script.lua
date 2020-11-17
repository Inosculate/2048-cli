options = {
    enable_colour = true,
    animate = true,
    grid_height = 4,
    grid_width = 4,
    spawn_rate = 1,
    ai = false,
    interactive = true
}

local animateTime = 160;

function onGameLoopIteration()
    animateTime = animateTime + 10;
    SetAnimateTime(animateTime);
end

local turns = 0;

function onGameLoopIterationComplete()
    turns = turns + 1
    if turns < 10 then
        Write("Great start!")
    elseif turns >= 10 then
        Write("We're on a roll")
    end

    local gamestate = getGameState();

    if gamestate.score_last >= 8 then
        Write("Cool, great merge of " .. tostring(gamestate.score_last))
    end
end