#include <stdio.h>
#include <stdlib.h>
#include "../include/device.h" // Function prototypes
#include "../include/constants.h" // DRIVER_PATH, NAME, EXEC, VERSION, SOURCE_CODE , COLOR_*
#include "../include/utils.h" // ifDirectoryExists, printError

#define COMMAND_LENGTH 128

// Implement control functions

bool conservationMode_control(bool value)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "sudo sh -c 'echo %d > %s/conservation_mode'", value, DRIVER_PATH);
    // Run and check if command succeed
    if (system(command) == 0)
    {
        printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Conservation mode %s" COLOR_CLEAN "\n", value ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
        return 0;
    }
    // Return 1 on failed action
    printError("Action failed", "conservation-mode");
    return 1;
}

bool usbCharging_control(bool value)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "sudo sh -c 'echo %d > %s/usb_charging'", value, DRIVER_PATH);
    // Run and check if command succeed
    if (system(command) == 0)
    {
        printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Usb charging %s" COLOR_CLEAN "\n", value ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
        return 0;
    }
    // Return 1 on failed action
    printError("Action failed", "usb-charging");
    return 1;
}

bool fnLock_control(bool value)
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "sudo sh -c 'echo %d > %s/fn_lock'", value, DRIVER_PATH);
    // Run and check if command succeed
    if (system(command) == 0)
    {
        printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Fn lock %s" COLOR_CLEAN "\n", value ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
        return 0;
    }
    // Return 1 on failed action
    printError("Action failed", "fn-lock");
    return 1;
}


// Function to get char output from bash command

char getChar(const char *command) {
    char output = ' ';
    FILE *pipe = popen(command, "r");
    if (pipe) {
        fscanf(pipe, "%c", &output);
        pclose(pipe);
    }
    return output;
}

// Implement status functions

bool conservationMode_status()
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "read -r value < %s/conservation_mode && echo $value", DRIVER_PATH);
    bool status = getChar(command) == '1' ? 1 : 0;
    printf(COLOR_CYAN "Status: " COLOR_CLEAN "Conservation mode %s" COLOR_CLEAN "\n", status ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
    return status;
}

bool usbCharging_status()
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "read -r value < %s/usb_charging && echo $value", DRIVER_PATH);
    bool status = getChar(command) == '1' ? 1 : 0;
    printf(COLOR_CYAN "Status: " COLOR_CLEAN "Usb charging %s" COLOR_CLEAN "\n", status ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
    return status;
}

bool fnLock_status()
{
    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "read -r value < %s/fn_lock && echo $value", DRIVER_PATH);
    bool status = getChar(command) == '1' ? 1 : 0;
    printf(COLOR_CYAN "Status: " COLOR_CLEAN "Fn lock %s" COLOR_CLEAN "\n", status ? COLOR_GREEN "[enabled]" : COLOR_RED "[disabled]");
    return status;
}
