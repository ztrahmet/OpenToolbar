#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // access()
#include "../include/utils.h" // Function prototypes
#include "../include/constants.h" // DRIVER_PATH, NAME, EXEC, VERSION, SOURCE_CODE , COLOR_*

void printError(char* title, char* msg)
{
    printf(COLOR_RED "%s: " COLOR_CLEAN "%s\n", title, msg);
}

bool ifDirectoryExists(char* path)
{
    if (access(path, F_OK) == 0)
        return true;
    printError("Invalid path", path);
    return false;
}
