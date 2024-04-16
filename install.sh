#!/bin/bash

# Check if there is already an installation
if [ -f /usr/local/bin/opentoolbar ]; then
    echo -n ":: OpenToolbar is already installed! Do you want to override [Y/n] "
    read -r response
    response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
    if [[ $response == "y" || $response == "yes" ]]; then echo ":: Overriding existing installation..."
    else
        echo -e "\e[31mTerminated\e[0m"
        return 1
    fi
fi

# Check if needed packages are not available
if ! command -v gcc &> /dev/null; then
    echo -e "\e[33mNeeded packages are not installed.\e[0m"

    if [ -x "$(command -v apt)" ]; then
        installCommand="apt install gcc"
    elif [ -x "$(command -v apt-get)" ]; then
        installCommand="apt-get install gcc"
    elif [ -x "$(command -v dnf)" ]; then
        installCommand="dnf install gcc"
    elif [ -x "$(command -v pacman)" ]; then
        installCommand="pacman -S gcc"
    elif [ -x "$(command -v zypper)" ]; then
        installCommand="zypper install gcc"
    else
        echo -e "\e[31mPackage manager not found.\e[0m Please install gcc manually."
        return 1
    fi

    if sudo $installCommand; then
        echo -e "\e[32mNeeded packages have been installed.\e[0m"
    else
        echo -e "\e[31mCould not install needed packages.\e[0m"
        return 1
    fi
fi

# Compile the C++ program and check the exit status
if sudo gcc -o /usr/local/bin/opentoolbar ./src/main.c ./src/device.c ./src/utils.c; then
    echo -e "\e[32mInstallation Completed Successfully.\e[0m\nUse 'opentoolbar --help' command to see options."
else
    echo -e "\e[31mFailed to install.\e[0m"
fi
