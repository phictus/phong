cmake_minimum_required(VERSION 3.10)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory("lib/glfw")
add_subdirectory("lib/glad")

project(phong LANGUAGES C)

add_executable(phong
    "src/main.c"
    "src/game.h"
    "src/game.c"
    "src/renderer.h"
    "src/renderer.c"
    "src/matrix.h"
    "src/matrix.c"
)
target_include_directories(phong
    PRIVATE
    "lib/glfw/include"
    "lib/glad/include"
)
target_link_libraries(phong
    PRIVATE
    "glfw"
    "glad"
    "opengl32"
)
set_property(TARGET phong PROPERTY C_STANDARD 11)
