#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <netinet/in.h>
#include <net/if.h>

// Structure to hold information about a network interface
typedef struct {
    char name[IF_NAMESIZE];    // Interface name
    char ip_address[INET6_ADDRSTRLEN];  // IP address
    char mac_address[18];  // MAC address
    int link_status;  // Link status (1: up, 0: down)
    char ip_class[16];  // IP address class (e.g., A, B, C)
    char broadcast_address[INET6_ADDRSTRLEN];  // Broadcast address
    int mtu;  // Maximum Transmission Unit (MTU)
    int is_promiscuous;  // Promiscuous mode status (1: enabled, 0: disabled)
} NetworkInterface;

// Function to retrieve information about available network interfaces
int get_network_interfaces(NetworkInterface** interfaces, int* count);

#endif /* NETWORK_INTERFACE_H */

