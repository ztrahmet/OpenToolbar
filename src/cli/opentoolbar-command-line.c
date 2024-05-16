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

#define VERSION "1.4.1"
#define SOURCE "https://github.com/ztrahmet/OpenToolbar"

#define RESET "\e[0m"
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
        strcmp(argv, "usb-charging") == 0)
    {
        return true;
    }
    // else
    return false;
}

int opentoolbarCommandLine(int argc, char* argv[])
{
    if (!isDirectory(DRIVER_DIRECTORY)) // Check driver directory for settings management
    {
        printf(YELLOW"W: "RESET"Driver directory is not valid, settings may not work.\n");
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
                if (strcmp(argv[i + 1], "0") == 0 || strcmp(argv[i + 1], "off") == 0)
                    value = '0';
                else if (strcmp(argv[i + 1], "1") == 0 || strcmp(argv[i + 1], "on") == 0)
                    value = '1';
                else
                {
                    printf(RED"E: "RESET"'%s' needs a value, <0|1> or <off|on>.\n", argv[i]);
                    continue;
                } // value handle

                if (setting_switch(argv[i], value) == 0)
                {
                    printf(YELLOW"Switch: "RESET"%s to %s"RESET"\n", argv[i], value == '1' ? GREEN"[ON]" : RED"[OFF]");
                }
                else
                    printf(RED"E: "RESET"Failed to switch %s %s.\n", argv[i], value == '1' ? "[ON]" : "[OFF]");

                // skip value next time
                ++i;
            }
            else
                printf(RED"E: "RESET"'%s' needs a value, <0|1> or <off|on>.\n", argv[i]);
        } // setting switch options

        else
            printf(RED"E: "RESET"'%s' is not an option.\n", argv[i]);

    }

    return 0;

}

void printHelp(const char* EXEC)
{
    printf("Usage:\n");
    printf("   %s [OPTIONS]\n", EXEC);
    printf("Options:\n");
    printf("   conservation-mode <0|1>       Enable or disable conservation mode\n");
    printf("   fn-lock <0|1>                 Enable or disable fn lock\n");
    printf("   usb-charging <0|1>            Enable or disable usb charging\n");
    printf("   -h, --help                    Show this help message\n");
    printf("   -i, --info                    Show general app information\n");
    printf("   -s, --status                  Show status information\n");
    printf("   -v, --version                 Show version information\n");
}

void printInfo(void)
{
    printf("OpenToolbar v"VERSION"\n");
    printf("SOURCE: "SOURCE"\n");
}

void printStatus(const char* setting)
{
    char status = setting_status(setting);
    if (status == '2') return; // do not write status for missing setting files
    printf(CYAN"Status: "RESET"%s is %s"RESET"\n", setting, status == '1' ? GREEN"[ON]" : RED"[OFF]");
}

void printVersion(void)
{
    printf(VERSION"\n");
}
