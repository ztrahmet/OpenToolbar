#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h" // DRIVER_PATH, NAME, EXEC, VERSION, SOURCE_CODE , COLOR_*

char command[128];

// Implement control functions
void conservationMode_control(char* value)
{
    if (strcmp(value, "1") == 0) {
        // Enable conservation mode
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/conservation_mode'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Conservation mode " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        }
    }
    else {
        // Disable conservation mode
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/conservation_mode'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Conservation mode " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
        }
    }
}

void usbCharging_control(char* value)
{
    if (strcmp(value, "1") == 0) {
        // Enable usb charging
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/usb_charging'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Usb charging " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        }
    }
    else {
        // Disable usb charging
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/usb_charging'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Usb charging " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
        }
    }
}

void fnLock_control(char* value)
{
    if (strcmp(value, "1") == 0) {
        // Enable fn lock
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/fn_lock'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Fn lock " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        }
    }
    else {
        // Disable fn lock
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/fn_lock'", DRIVER_PATH);
        if (system(command) == 0) {
            printf(COLOR_YELLOW "Action: " COLOR_CLEAN "Fn lock " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
        }
    }
}

// Function to get char output from bash command
char getOutput(const char *command) {
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
    snprintf(command, sizeof(command), "read -r value < %s/conservation_mode && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Conservation mode " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        return 1;
    }
    printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Conservation mode " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
    return 0;
}

bool usbCharging_status()
{
    snprintf(command, sizeof(command), "read -r value < %s/usb_charging && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Usb charging " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        return 1;
    }
    printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Usb charging " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
    return 0;
}

bool fnLock_status()
{
    snprintf(command, sizeof(command), "read -r value < %s/fn_lock && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Fn lock " COLOR_GREEN "[enabled]" COLOR_CLEAN "\n");
        return 1;
    }
    printf(COLOR_YELLOW "Status: " COLOR_CLEAN "Fn lock " COLOR_RED "[disabled]" COLOR_CLEAN "\n");
    return 0;
}
