/* opentoolbar-settings-management.h
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

#ifndef OPENTOOLBAR_SETTINGS_MANAGEMENT_H
#define OPENTOOLBAR_SETTINGS_MANAGEMENT_H

#define DRIVER_DIRECTORY "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00"

int directoryExists(void);

int setting_switch(const char*, const char);

char setting_status(const char*);

#endif /* OPENTOOLBAR_SETTINGS_MANAGEMENT_H */
