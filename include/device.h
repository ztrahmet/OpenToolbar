#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"

char command[128];

// Implement control functions
void conservationMode_control(char* value)
{
    if (strcmp(value, "0") == 0) {
        // Disable conservation mode
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/conservation_mode'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Conservation mode \e[31m[disabled]\e[0m\n");
        }
    }
    else {
        // Enable conservation mode
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/conservation_mode'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Conservation mode \e[32m[enabled]\e[0m\n");
        }
    }
}

void usbCharging_control(char* value)
{
    if (strcmp(value, "0") == 0) {
        // Disable usb charging
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/usb_charging'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Usb charging \e[31m[disabled]\e[0m\n");
        }
    }
    else {
        // Enable usb charging
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/usb_charging'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Usb charging \e[32m[enabled]\e[0m\n");
        }
    }
}

void fnLock_control(char* value)
{
    if (strcmp(value, "0") == 0) {
        // Disable fn lock
        snprintf(command, sizeof(command), "sudo sh -c 'echo 0 > %s/fn_lock'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Fn lock \e[31m[disabled]\e[0m\n");
        }
    }
    else {
        // Enable fn lock
        snprintf(command, sizeof(command), "sudo sh -c 'echo 1 > %s/fn_lock'", DRIVER_PATH);
        if (system(command) == 0) {
            printf("\e[33mAction:\e[0m Fn lock \e[32m[enabled]\e[0m\n");
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
    snprintf(command, sizeof(command), "read -r -n 1 value < %s/conservation_mode && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf("\e[33mStatus:\e[0m Conservation mode \e[32m[enabled]\e[0m\n");
        return 1;
    }
    printf("\e[33mStatus:\e[0m Conservation mode \e[31m[disabled]\e[0m\n");
    return 0;
}

bool usbCharging_status()
{
    snprintf(command, sizeof(command), "read -r -n 1 value < %s/usb_charging && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf("\e[33mStatus:\e[0m Usb charging \e[32m[enabled]\e[0m\n");
        return 1;
    }
    printf("\e[33mStatus:\e[0m Usb charging \e[31m[disabled]\e[0m\n");
    return 0;
}

bool fnLock_status()
{
    snprintf(command, sizeof(command), "read -r -n 1 value < %s/fn_lock && echo $value", DRIVER_PATH);
    bool status = getOutput(command)=='1'? 1: 0;
    if (status)
    {
        printf("\e[33mStatus:\e[0m Fn lock \e[32m[enabled]\e[0m\n");
        return 1;
    }
    printf("\e[33mStatus:\e[0m Fn lock \e[31m[disabled]\e[0m\n");
    return 0;
}
