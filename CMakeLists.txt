cmake_minimum_required(VERSION 3.0)
project(opentoolbar C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
file(GLOB MAIN
        "src/*"
        "src/cli/*"
)
add_executable(opentoolbar ${MAIN})
