cmake_minimum_required(VERSION 3.25)
project(part1)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(include)
include_directories(include/glad)
include_directories(include/KHR)
include_directories(include/glm)

add_executable(part1
        include/glad/glad.h
        include/KHR/khrplatform.h
        include/Particle.hpp
        include/Simulation.hpp
        src/glad.cpp
        src/Particle.cpp
        src/Simulation.cpp
        src/main.cpp include/Shader.hpp src/Shader.cpp include/Render.hpp src/Render.cpp)

target_link_libraries(part1 ${SDL2_LIBRARIES})