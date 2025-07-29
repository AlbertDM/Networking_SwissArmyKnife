// network_interface_info.c

/// In this file goes all the information that can be taken directly from the array.

#include "network_interface.h"
#include <stdio.h>
#include <stdlib.h>

int getIPClass(int index, const NetworkInterface* interfaces, char* ipClass) {
    // Implementation of getIPClass
}

int getBroadcastAddress(int index, const NetworkInterface* interfaces, char* broadcastAddress) {
    // Implementation of getBroadcastAddress
}

int getMTU(int index, const NetworkInterface* interfaces, int* mtu) {
    // Implementation of getMTU
}

int getMACAddress(int index, const NetworkInterface* interfaces, char* macAddress) {
    // Implementation of getMACAddress
}

int getIPAddress(int index, const NetworkInterface* interfaces, char* ipAddress) {
    // Implementation of getIPAddress
}

int getLinkStatus(int index, const NetworkInterface* interfaces, int* status) {
    // Implementation of getLinkStatus
}

/**
 * @brief Retrieve the subnet mask of a network interface.
 *
 * Gets the netmask of the interface in dotted decimal format.
 *
 * @param index Index of the interface.
 * @param interfaces Array of NetworkInterface structures.
 * @param netmask Output buffer for the netmask.
 * @return 0 on success, -1 on failure.
 */
int getNetmask(int index, const NetworkInterface* interfaces, char* netmask) {
    // TODO: implement this
    return 0;
}

/**
 * @brief Get the type of a network interface.
 *
 * Types may include Ethernet, loopback, VLAN, etc.
 *
 * @param index Index of the interface.
 * @param interfaces Array of NetworkInterface structures.
 * @param type Output buffer for the interface type string.
 * @return 0 on success, -1 on failure.
 */
int getInterfaceType(int index, const NetworkInterface* interfaces, char* type) {
    // TODO: implement this
    return 0;
}



// ... other information functions

