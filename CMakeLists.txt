cmake_minimum_required(VERSION 3.0)
project(opentoolbar C)
set(CMAKE_C_STANDARD 99)

# Collect source files
file(GLOB MAIN
        "src/*"
        "src/cli/*"
)

# Create executable
add_executable(opentoolbar ${MAIN})

# Install opentoolbar executable to bin directory
install(TARGETS opentoolbar DESTINATION bin)
