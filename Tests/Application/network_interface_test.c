#include <stdio.h>
#include "network_interface.h"

void print_interface_info(NetworkInterface* iface) {
    printf("Interface Name: %s\n", iface->name);
    printf("IP Address: %s\n", iface->ip_address);
    printf("MAC Address: %s\n", iface->mac_address);
    printf("Link Status: %s\n", (iface->link_status == 1) ? "Up" : "Down");
    printf("IP Class: %s\n", iface->ip_class);
    printf("Broadcast Address: %s\n", iface->addr.broadcast);
    printf("MTU: %d\n", iface->mtu);
    printf("Promiscuous Mode: %s\n", (iface->is_promiscuous == 1) ? "Enabled" : "Disabled");
    printf("-------------------------------------\n");
}

int main() {
    NetworkInterface* interfaces;
    int count;
    int i;

    // Retrieve information about network interfaces
    int result = get_network_interfaces(&interfaces, &count);
    if (result == -1) {
        printf("Failed to retrieve network interface information.\n");
        return -1;
    }

    // Print information about each interface
    for (i = 0; i < count; i++) {
        print_interface_info(&interfaces[i]);
    }

    // Clean up memory
    free(interfaces);

    return 0;
}

