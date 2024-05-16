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

#define COMMAND_LENGTH 128

int directoryExists(void) {
    return system("[ -d '"DRIVER_DIRECTORY"' ]");
}

int setting_switch(const char* setting, const char value)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "sudo sh -c 'echo %c >"DRIVER_DIRECTORY"/$(echo %s|sed 's/-/_/g')'>/dev/null 2>&1", value, setting);
    return system(command);
}

char setting_status(const char* setting)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "grep -q '^1' "DRIVER_DIRECTORY"/$(echo %s|sed 's/-/_/g')>/dev/null 2>&1", setting);
    return system(command) == 0 ? '1' : '0';
}
