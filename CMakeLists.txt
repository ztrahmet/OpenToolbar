cmake_minimum_required(VERSION 3.0)
project(opentoolbar C)
set(CMAKE_C_STANDARD 99)

# Collect source files
file(GLOB SRC
        "src/*"
        "src/cli/*"
)

# Create executable
add_executable(opentoolbar ${SRC})

# Install opentoolbar executable to bin directory
install(TARGETS opentoolbar DESTINATION /usr/bin)

# Install opentoolbar bash-completion to completions directory
install(PROGRAMS bash-completion DESTINATION /usr/share/bash-completion/completions RENAME opentoolbar)

# Create make uninstall option
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
        TARGET "uninstall"
        POST_BUILD
        COMMENT "Uninstall files with install_manifest.txt"
        COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
                install_manifest.txt to be uninstalled!
)
