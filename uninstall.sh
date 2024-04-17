#!/bin/bash

# Check if there is already an installation
if [ -f /usr/local/bin/opentoolbar ]; then
    echo -n ":: Do you really want to completely remove opentoolbar [Y/n] "
    read -r response
    response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
    # Check user response
    if [[ $response != "y" && $response != "yes" ]]; then
        echo -e "\e[31mTerminated\e[0m"
        return 1
    fi
    # Contiue remove
    if sudo rm /usr/local/bin/opentoolbar; then
        sudo rm /usr/share/bash-completion/completions/opentoolbar
        echo -e "\e[93mUninstalled.\e[0m"
        return 0
    fi
    echo -e "\e[31mUnexpected error:\e[0m Could not remove."
else
    echo -e "\e[31mNo installation found.\e[0m"
    return 1
fi