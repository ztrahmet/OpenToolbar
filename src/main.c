#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constants.h" // DRIVER_PATH, NAME, EXEC, VERSION, SOURCE_CODE , COLOR_*
#include "../include/device.h" // conservationMode, usbCharging, fnLock

int main(int argc, char* argv[])
{
    // Checking if driver directory exist
    int status = system("[ -d \"" DRIVER_PATH "\" ]");
    if (status != 0) {
        printf(COLOR_RED "Driver directory does not exists.\n" COLOR_CLEAN);
        return 1;
    }

    // Check if there are not sufficient command-line arguments
    if (argc < 2)
    {
        printf("Use '%s --help' command to see options.\n", EXEC);
        return 1;
    }

    // Handle command-line arguments in loop
    for (unsigned short i = 1; i < argc; i++)
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
        {
            printf("%s %s\nSource: %s\n", NAME, VERSION, SOURCE_CODE);
        }

        // Handle status argument
        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--status"))
        {
            printf("------------------------------------------------------------------------\n");
            conservationMode_status();
            usbCharging_status();
            fnLock_status();
            printf("------------------------------------------------------------------------\n");
        }

        // Handle arguments that need value
        else if (i + 1 == argc) printf(COLOR_RED "Invalid Usage: " COLOR_CLEAN "%s\n", argv[i]);
        else if (!strcmp(argv[i+1], "0") || !strcmp(argv[i+1], "1"))
        {
            if (!strcmp(argv[i], "conservation-mode")) conservationMode_control(argv[++i]);
            else if (!strcmp(argv[i], "usb-charging")) usbCharging_control(argv[++i]);
            else if (!strcmp(argv[i], "fn-lock")) fnLock_control(argv[++i]);

            // If none of the above return error and skip value
            else printf(COLOR_RED "Invalid Usage: " COLOR_CLEAN "%s\n", argv[i++]);
        }
        else printf(COLOR_RED "Invalid Usage: " COLOR_CLEAN "%s\n", argv[i]);
    }
    return 0;
}
