#include <stdio.h>
#include <stdbool.h>
#include "ai.h"
#include "engine.h"
#include "gfx.h"
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <memory>
#include "Script.h"

std::unique_ptr<Script> script;

void draw_then_sleep(struct gfx_state *s, struct gamestate *g, const std::string& msg)
{
    gfx_draw(s, g, msg);
    /* Have a fixed time for each turn to animate (160 default) */
    gfx_sleep(script->GetAnimateTime() / g->opts->grid_width);
}

char *targetDir(char *env, char *path)
{
    char *dir;
    char *dirEnv;
    dirEnv = getenv(env);
    dir = (char*)malloc(strlen(dirEnv) + strlen(path) + 1);
    strcpy(dir, dirEnv);
    strcat(dir,path);
    return dir;
}

int main(int argc, char **argv)
{   
    setlocale (LC_ALL, "");
    bindtextdomain ("gfx_terminal", targetDir("PWD","/18n/"));
    textdomain ("gfx_terminal");

    struct gamestate *g = gamestate_init(argc, argv);
    if (!g) {
        fatal("failed to allocate gamestate");
    }

    script = std::make_unique<Script>(g);
    script->ParseOptions(g->opts);

    struct gfx_state *s = NULL;

    if (g->opts->interactive) {
        s = gfx_init(g);
        if (!s) {
            fatal("failed to allocate gfx state");
        }
    }

    int game_running = true;
    while (game_running) {
        
        script->OnGameLoopIteration();

        if (g->opts->interactive)
            gfx_draw(s, g, script->GetMessage());

get_new_key:;
        int direction = dir_invalid;
        int value = !g->opts->ai ? gfx_getch(s) : ai_move(g);
        switch (value) {
            case 'h':
            case 'a':
	    case INPUT_LEFT:
                direction = dir_left;
                break;
            case 'l':
            case 'd':
	    case INPUT_RIGHT:
                direction = dir_right;
                break;
            case 'j':
            case 's':
	    case INPUT_DOWN:
                direction = dir_down;
                break;
            case 'k':
            case 'w':
	    case INPUT_UP:
                direction = dir_up;
                break;
            case 'q':
                game_running = false;
                break;
            default:
                goto get_new_key;
        }

        /* Game will only end if 0 moves available */
        if (game_running) {
            gamestate_tick(s, g, direction, g->opts->animate && g->opts->interactive
                    ? draw_then_sleep : NULL, script->GetMessage());

            if (g->moved == 0)
                goto get_new_key;

            int spawned;
            for (spawned = 0; spawned < g->opts->spawn_rate; spawned++)
                gamestate_new_block(g);

            if (gamestate_end_condition(g)) {
                game_running = false;
            }
        }

        script->OnGameLoopIterationComplete();
    }

    if (g->opts->interactive) {
        // gfx_getch(s);   // getch here would be good,
                         // need an exit message for each graphical output
        gfx_destroy(s);
    }

    printf("%ld\n", g->score);
    gamestate_clear(g);
    return 0;
}
