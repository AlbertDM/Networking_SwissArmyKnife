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



// ... other information functions

