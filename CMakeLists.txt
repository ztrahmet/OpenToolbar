cmake_minimum_required(VERSION 3.0)
project(opentoolbar C)
set(CMAKE_C_STANDARD 99)

# Collect source files
file(GLOB SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cli/*
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

# CPACK

set(CPACK_PACKAGE_NAME "opentoolbar")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_CONTACT "contact@ztrahmet.net")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Manage device features")
set(CPACK_PACKAGE_DESCRIPTION "Unofficial application to manage Lenovo Laptop features, such as conservation mode, on GNU/Linux.")

# DEB

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ahmet Öztürk")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")

# Include CPack
include(CPack)
