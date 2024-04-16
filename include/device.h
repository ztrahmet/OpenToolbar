#ifndef DEVICE_H
#define DEVICE_H

#include <stdbool.h>

// Function prototypes

// Control functions return 1 on failed action
bool conservationMode_control(bool value);
bool usbCharging_control(bool value);
bool fnLock_control(bool value);

// Status functions to return true/false information
bool conservationMode_status();
bool usbCharging_status();
bool fnLock_status();

#endif /* DEVICE_H */
