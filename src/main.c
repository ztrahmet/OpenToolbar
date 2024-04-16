#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // bool
#include <unistd.h> // access()
#include "../include/constants.h" // DRIVER_PATH, NAME, EXEC, VERSION, SOURCE_CODE , COLOR_*
#include "../include/device.h" // conservationMode, usbCharging, fnLock

// Function prototypes
bool ifDirectoryExists(const char*);
void printError(char*, char*);

int main(int argc, char* argv[])
{
    // Checking if driver directory exists
    if (!ifDirectoryExists(DRIVER_PATH))
        return 1;

    // Check if there are sufficient command-line arguments
    if (argc < 2)
    {
        printf("Use '%s --help' command to see options.\n", EXEC);
        return 1;
    }

    // Handle command-line arguments in loop
    for (int i = 1; i < argc; i++)
    {
        // Handle help argument
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printf("Usage:\n");
            printf("   %s [OPTIONS]\n", EXEC);
            printf("Options:\n");
            printf("   conservation-mode <0|1>   Enable or disable conservation mode\n");
            printf("   usb-charging <0|1>        Enable or disable usb charging\n");
            printf("   fn-lock <0|1>             Enable or disable fn lock\n");
            printf("   -s, --status              Show status information\n");
            printf("   -v, --version             Show version information\n");
            printf("   -h, --help                Show this help message\n");
        }

        // Handle version argument
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
            printf("%s %s\nSource: %s\n", NAME, VERSION, SOURCE_CODE);

        // Handle status argument
        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--status"))
        {
            printf("------------------------------------------------------------------------\n");
            conservationMode_status();
            usbCharging_status();
            fnLock_status();
            printf("------------------------------------------------------------------------\n");
        }

        /*
            Handle arguments that need value
        */

        else if (i + 1 < argc)
        {
            // Handle value
            bool value = false;
            if(strcmp(argv[i+1], "1") == 0 || strcmp(argv[i+1], "true") == 0 || strcmp(argv[i+1], "enable") == 0)
                value = true;
            else if(strcmp(argv[i+1], "0") != 0 && strcmp(argv[i+1], "false") != 0 && strcmp(argv[i+1], "disable") != 0)
            {
                printError("Invalid Usage",argv[i]);
                continue;
            }

            if (strcmp(argv[i], "conservation-mode") == 0)
                conservationMode_control(value);
            else if (strcmp(argv[i], "usb-charging") == 0)
                usbCharging_control(value);
            else if (strcmp(argv[i], "fn-lock") == 0)
                fnLock_control(value);
            else
                printError("Invalid Usage",argv[i]);

            // Skip value
            ++i;
        }
        else
            printError("Invalid Usage",argv[i]);
    }
    return 0;
}

bool ifDirectoryExists(const char* path)
{
    if (access(path, F_OK) == 0)
        return true;
    printError("Invalid path", DRIVER_PATH);
    return false;
}

void printError(char* title, char* msg)
{
    printf(COLOR_RED "%s: " COLOR_CLEAN "%s\n", title, msg);
}
