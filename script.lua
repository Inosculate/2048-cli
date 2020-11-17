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