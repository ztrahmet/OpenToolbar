#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constants.h"
#include "../include/device.h"

int main(int argc, char* argv[])
{
    // Checking if driver directory exist
    int status = system("[ -d \"" DRIVER_PATH "\" ]");
    if (status != 0) {
        printf("\e[31mDriver directory does not exists.\e[0m\n");
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
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printf("Usage:\n");
            printf("   %s [OPTIONS]\n", EXEC);
            printf("Options:\n");
            printf("   conservation-mode <0|1>   Enable (1) or disable (0) conservation mode\n");
            printf("   usb-charging <0|1>        Enable (1) or disable (0) usb charging\n");
            printf("   fn-lock <0|1>             Enable (1) or disable (0) fn lock\n");
            printf("   -s, --status              Show status information\n");
            printf("   -v, --version             Show version information\n");
            printf("   -h, --help                Show this help message\n");
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
        {
            printf("%s %s\nSource: %s\n", NAME, VERSION, SOURCE_CODE);
        }
        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--status"))
        {
            printf("------------------------------------------------------------------------\n");
            conservationMode_status();
            usbCharging_status();
            fnLock_status();
            printf("------------------------------------------------------------------------\n");
        }

        // Handle arguments that need value
        else if (i + 1 == argc);
        else if (!strcmp(argv[i+1], "0") || !strcmp(argv[i+1], "1"))
        {
            if (!strcmp(argv[i], "conservation-mode")) conservationMode_control(argv[++i]);
            if (!strcmp(argv[i], "usb-charging")) usbCharging_control(argv[++i]);
            if (!strcmp(argv[i], "fn-lock")) fnLock_control(argv[++i]);
        }
    }
    return 0;
}
