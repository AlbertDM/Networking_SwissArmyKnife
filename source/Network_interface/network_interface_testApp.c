#include <stdio.h>
#include "network_interface.h"

int main() {
    // Test getNetworkInterfaces
    NetworkInterface* interfaces;
    int count;
    int result = getNetworkInterfaces(&interfaces, &count);
    if (result == 0) {
        printf("Number of interfaces: %d\n", count);
        for (int i = 0; i < count; i++) {
            printf("Interface %d:\n", i+1);
            printf("Name: %s\n", interfaces[i].name);
            printf("IP Address: %s\n", interfaces[i].ip_address);
            printf("MAC Address: %s\n", interfaces[i].mac_address);
            printf("Link Status: %d\n", interfaces[i].link_status);
            printf("IP Class: %s\n", interfaces[i].ip_class);
            printf("Broadcast Address: %s\n", interfaces[i].broadcast_address);
            printf("MTU: %d\n", interfaces[i].mtu);
            printf("Promiscuous Mode: %d\n", interfaces[i].is_promiscuous);
            printf("---------------------\n");
        }
        free(interfaces);
    } else {
        printf("Failed to retrieve network interfaces.\n");
    }

    // Test getPromiscuousMode
    const char* interfaceName = "eth0"; // Replace with desired interface name
    int promiscuousMode = getPromiscuousMode(interfaceName);
    if (promiscuousMode != -1) {
        printf("Promiscuous mode status for interface %s: %d\n", interfaceName, promiscuousMode);
    } else {
        printf("Failed to retrieve promiscuous mode status for interface %s\n", interfaceName);
    }

    // Test setPromiscuousMode
    int enable = 1; // 1 to enable, 0 to disable
    int setPromiscuousResult = setPromiscuousMode(interfaceName, enable);
    if (setPromiscuousResult == 0) {
        printf("Promiscuous mode set successfully for interface %s\n", interfaceName);
    } else {
        printf("Failed to set promiscuous mode for interface %s\n", interfaceName);
    }

    return 0;
}
