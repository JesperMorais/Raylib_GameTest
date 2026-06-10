cmake_minimum_required(VERSION 3.15)
project(CoolGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- raylib (downloaded & built automatically) ---------------------------
# Fetched instead of using the bundled lib/libraylib.a, which is MinGW-only;
# this way the project builds with whatever compiler CMake picks (MSVC here).
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)  # don't build raylib's examples
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        6.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(raylib)

# --- the game ------------------------------------------------------------
# Source files (mirrors run.ps1). The rest of the game logic lives in *.hpp
# headers that are #included, so only the .cpp files are listed here.
add_executable(main
    main.cpp
    game.cpp
    screen.cpp
    handleCamera.cpp
    handlePlayer.cpp
    handleEnemy.cpp
    handleMenu.cpp
    handleObjektiv.cpp
)

# raylib's target carries its own include dirs and the opengl32/gdi32/winmm
# system links, so just link to it.
target_link_libraries(main PRIVATE raylib)

# Match run.ps1's warnings on GCC/Clang; MSVC doesn't understand those flags.
if(NOT MSVC)
    target_compile_options(main PRIVATE -Wall -Wshadow)
endif()

# The game loads assets with paths relative to the working directory
# (e.g. "models/map.glb", "sounds/Jeppohoj.wav"), so place main.exe in the
# project root next to those folders, just like the old run.ps1 did. The
# per-config variants keep it out of a Debug/Release subfolder when built
# with a multi-config generator like Visual Studio.
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}"
)
