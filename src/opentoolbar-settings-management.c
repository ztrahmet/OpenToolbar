/* opentoolbar-settings-management.c
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

#include "opentoolbar-settings-management.h" // Function Prototypes

#include <stdio.h>
#include <stdlib.h> // system()
#include <unistd.h> // access()

#define COMMAND_LENGTH 256

bool isDirectory(const char PATH[])
{
    if (access(PATH, F_OK) == 0)
        return true;
    else
        return false;
}

char getStatus(const char command[])
{
    FILE* pipe = popen(command, "r");
    if (pipe)
    {
        char output;
        fscanf(pipe, "%c", &output);
        pclose(pipe);
        if (output == '\0')
            return '2'; // return '2' for missing setting files
        // else
        return output == '1' ? '1' : '0';
    }
    // else
    return '2';
}

int setting_switch(const char* setting, const char value)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "echo \"%c\" | sudo tee "DRIVER_DIRECTORY"/$(echo \"%s\" | sed 's/-/_/g') &> /dev/null", value, setting);
    if (system(command) == 0)
        return 0; // succeed
    // else
    return 1; // failed
}

char setting_status(const char* setting)
{
    isDirectory(DRIVER_DIRECTORY"");
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "if [ -f \""DRIVER_DIRECTORY"/$(echo '%s' | sed 's/-/_/g')\" ]; then\n read -r value < \""DRIVER_DIRECTORY"/$(echo '%s' | sed 's/-/_/g')\" && echo \"$value\"; fi", setting, setting);
    return getStatus(command); // returns '2' when setting file is missing
}
