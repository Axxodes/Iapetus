cmake_minimum_required(VERSION 3.20)

project(Iapetus LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# GLAD2
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

FetchContent_MakeAvailable(glfw glad)

# Generate GLAD loader
glad_add_library(glad REPRODUCIBLE API gl:core=4.6)

add_executable(Iapetus
    src/main.cpp
)

target_link_libraries(Iapetus PRIVATE
    glfw
    glad
    opengl32
)