cmake_minimum_required(VERSION 3.4.1)
project(2048)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -DINVERT_COLORS -DVT100")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -fpermissive")

add_subdirectory(ThirdParty/sol3)

link_directories(${CONAN_LIB_DIRS})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CPP_SOURCE src/Script.cpp src/main.cpp )

set(C_SOURCE 
    src/ai.cpp
    src/options.cpp
    src/highscore.cpp 
    src/engine.cpp
)

set(TERMINAL_SOURCE src/gfx_terminal.cpp)

set(NCURSES_SOURCE src/gfx_curses.cpp)

if(NCURSES)
    list(APPEND SOURCES ${C_SOURCE} ${CPP_SOURCE} ${NCURSES_SOURCE})
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    include_directories(/usr/share/gettext/)
else()
    list(APPEND SOURCES ${C_SOURCE} ${CPP_SOURCE} ${TERMINAL_SOURCE})
endif()

find_package(Lua 5.3 REQUIRED)

message(STATUS ${LUA_INCLUDE_DIR})

include_directories(src)
include_directories(${LUA_INCLUDE_DIR})

add_executable(2048 ${SOURCES})

target_link_libraries(2048 sol2)
target_link_libraries(2048 ${LUA_LIBRARIES})

if(NCURSES)
    target_link_libraries(2048 ${CURSES_LIBRARIES})
    target_link_libraries(2048 ${INTL_LIBRARIES})
endif()
