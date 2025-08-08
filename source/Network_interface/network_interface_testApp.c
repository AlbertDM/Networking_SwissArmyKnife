#include <stdio.h>
#include <stdlib.h>
#include "network_interface.h"

int main() {
    // Test getNetworkInterfaces
    NetworkInterface* interfaces;
    int count;
    int result = getNetworkInterfaces(&interfaces, &count);
    if (result == 0) {
        printf("\n\nNumber of interfaces: %d\n", count);
        printf("---------------------\n");
        for (int i = 0; i < count; i++) {
            printf("Interface: %d\n", i+1);
            printf("Name: %s\n", interfaces[i].name);
            printf("IP Address: ");
            for (int j = 0; j < 4; j++) {
              printf("%d", interfaces[i].addr.ip[j]);
              if (j < 3) {
                printf(".");
              }
            }
            printf("\n");
            printf("MAC Address: ");
            for (int j = 0; j < 6; j++) {
              printf("%02X", interfaces[i].mac[j]);
              if (j < 5) {
                printf(":");
              }
            }
            printf("\n");
            printf("Link Status: %d\n", interfaces[i].link.link_status);
            /* Legacy: printf("IP Class: %s\n", interfaces[i].ip_class); */
            printf("Broadcast Address: %s\n", interfaces[i].addr.broadcast);
            printf("MTU: %d\n", interfaces[i].addr.mtu);
            printf("Promiscuous Mode: %d\n", interfaces[i].link.is_promiscuous);
            printf("---------------------\n");
        }
        free(interfaces);
    } else {
        printf("Failed to retrieve network interfaces.\n");
    }

    // Test getPromiscuousMode
    const char* interfaceName = "enp0s20f0u2"; // Replace with desired interface name
    int index = getInterfaceIndexByName(interfaceName, interfaces, count);
    int promiscuousMode = getPromiscuousMode(index, interfaces, count);
    if (promiscuousMode != -1) {
        printf("Promiscuous mode status for interface %s: %d\n", interfaceName, promiscuousMode);
    } else {
        printf("Failed to retrieve promiscuous mode status for interface %s\n", interfaceName);
    }

    // // Test setPromiscuousMode
    // int enable = 1; // 1 to enable, 0 to disable
    // int setPromiscuousResult = setPromiscuousMode(interfaceName, enable);
    // if (setPromiscuousResult == 0) {
    //     printf("Promiscuous mode set successfully for interface %s\n", interfaceName);
    // } else {
    //     printf("Failed to set promiscuous mode for interface %s\n", interfaceName);
    // }

    return 0;
}
