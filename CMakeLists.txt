cmake_minimum_required(VERSION 3.4.1)

project(2048)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -DINVERT_COLORS -DVT100")

set(CPP_SOURCE 
    src/lua.cpp
)

set(C_SOURCE 
    src/ai.c 
    src/options.c 
    src/main.c 
    src/highscore.c 
    src/engine.c
    src/merge_std.c
)

set(TERMINAL_SOURCE
    src/gfx_terminal.c
)

set(NCURSES_SOURCE
    src/gfx_curses.c
)

if(NCURSES)
    list(APPEND SOURCES ${C_SOURCE} ${CPP_SOURCE} ${NCURSES_SOURCE})
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    include_directories(/usr/share/gettext/)
else()
    list(APPEND SOURCES ${C_SOURCE} ${CPP_SOURCE} ${TERMINAL_SOURCE})
endif()

include_directories(src)

add_executable(2048 ${SOURCES})

if(NCURSES)
    target_link_libraries(2048 ${CURSES_LIBRARIES})
    target_link_libraries(2048 ${INTL_LIBRARIES})
endif()
