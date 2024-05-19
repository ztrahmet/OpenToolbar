/* opentoolbar-command-line.c
 *
 * Copyright 2024 Ahmet Öztürk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "opentoolbar-command-line.h" // Function Prototypes

#include "../opentoolbar-settings-management.h"

#include <stdio.h>
#include <string.h> // strcmp()
#include <stdbool.h> // bool

#define VERSION "1.4.3"
#define SOURCE "https://github.com/ztrahmet/OpenToolbar"
#define LICENSE "GPL-3.0"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define CYAN "\e[36m"

void printHelp(const char*);
void printInfo(void);
void printStatus(const char*);
void printVersion(void);

bool isSetting(const char* argv)
{
    if (strcmp(argv, "conservation-mode") == 0 ||
        strcmp(argv, "fn-lock") == 0 ||
        strcmp(argv, "touchpad") == 0 ||
        strcmp(argv, "usb-charging") == 0)
    {
        return true;
    }
    // else
    return false;
}

int opentoolbarCommandLine(int argc, char* argv[])
{
    if (directoryExists() != 0) // Check driver directory for settings management
    {
        printf(YELLOW"W: "RESET"Driver directory is not valid, settings will not work.\n");
    }

    for (int i = 1; i < argc; ++i)
    {

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printHelp(argv[0]);
            return 0;
        } // help option
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--info") == 0)
        {
            printInfo();
            return 0;
        } // info option
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printVersion();
            return 0;
        } // version option
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--status") == 0)
        {
            if (++i == argc)
            {
                printStatus("conservation-mode");
                printStatus("fn-lock");
                printStatus("touchpad");
                printStatus("usb-charging");
            }
            else
            {
                for (int j = i; j < argc; ++j)
                {
                    if (isSetting(argv[j]))
                        printStatus(argv[j]);
                    else
                        printf(RED"E: "RESET"'%s' is not a setting.\n", argv[j]);
                }
            }
            return 0;
        } // status option

        if (isSetting(argv[i]))
        {
            if (i < argc - 1)
            {
                char value;
                if (strcmp(argv[i + 1], "0") == 0 || strcmp(argv[i + 1], "false") == 0)
                    value = '0';
                else if (strcmp(argv[i + 1], "1") == 0 || strcmp(argv[i + 1], "true") == 0)
                    value = '1';
                else
                {
                    printf(RED"E: "RESET"'%s' needs a bool value.\n", argv[i]);
                    continue;
                } // value handle

                if (setting_switch(argv[i], value) == 0)
                {
                    printf(YELLOW"Switch: %s "RESET"%s\n", value == '1' ? GREEN"▣" : RED"□", argv[i]);
                }
                else
                    printf(RED"E: "RESET"Failed to switch %s.\n", argv[i]);

                // skip value next time
                ++i;
            }
            else
                printf(RED"E: "RESET"'%s' needs a bool value.\n", argv[i]);
        } // setting switch options

        else
            printf(RED"E: "RESET"'%s' is not an option.\n", argv[i]);

    }

    return 0;

}

void printHelp(const char* EXEC)
{
    printf(UNDERLINE BOLD"Usage:\n"RESET);
    printf("   "BOLD"%s "RESET ITALIC"<options>"RESET"\n", EXEC);
    printf(UNDERLINE BOLD"Options:\n"RESET);
    printf("   "ITALIC"<setting> <bool>"RESET"           Enable or disable a setting\n");
    printf("   "BOLD"-h, --help"RESET"                 Show this help message\n");
    printf("   "BOLD"-i, --info"RESET"                 Show general app information\n");
    printf("   "BOLD"-s, --status "RESET ITALIC"<?settings>"RESET"   Show current status of the settings\n");
    printf("   "BOLD"-v, --version"RESET"              Show version information\n");
    printf(UNDERLINE BOLD"Settings:\n"RESET);
    printf("   "BOLD"conservation-mode"RESET"          Limit battery percentage to 60 for battery health\n");
    printf("   "BOLD"fn-lock"RESET"                    Lock Fn key to use F1-F12 as default\n");
    printf("   "BOLD"touchpad"RESET"                   Enable/disbale touchpad\n");
    printf("   "BOLD"usb-charging"RESET"               Always on usb port for charging other devices\n");
}

void printInfo(void)
{
    printf("OpenToolbar v"VERSION"\n");
    printf("Source:  "ITALIC SOURCE RESET"\n");
    printf("License: "LICENSE"\n");
}

void printStatus(const char* setting)
{
    if (fileExists(setting) != 0)
        return; // don't write status if setting file doesn't exist
    char status = setting_status(setting);
    printf(CYAN"Status: %s "RESET"%s\n", status == '1' ? GREEN"▣" : RED"□", setting);
}

void printVersion(void)
{
    printf(VERSION"\n");
}
