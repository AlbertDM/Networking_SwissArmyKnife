#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#ifdef _WIN32
// Windows Includes and defines.

#include <winsock2.h>
#include <iphlpapi.h>
#include <Ws2tcpip.h> // Definition of INET6_ADDRSTRLEN


#define INTERFACE_NAME_LENGTH MAX_ADAPTER_NAME_LENGTH


#else   
// Linux Includes and defines.


#include <netinet/in.h>
#include <net/if.h>

#define INTERFACE_NAME_LENGTH IF_NAMESIZE

#endif

#define MAC_ADDRESS_STRLEN 18
#define IP_CLASS_LEN 16

// Structure to hold information about a network interface.
typedef struct {
    char name[INTERFACE_NAME_LENGTH];    // Interface name
    char ip_address[INET6_ADDRSTRLEN];  // IP address
    char mac_address[MAC_ADDRESS_STRLEN];  // MAC address
    int link_status;  // Link status (1: up, 0: down)
    char ip_class[IP_CLASS_LEN];  // IP address class (e.g., A, B, C)
    char broadcast_address[INET6_ADDRSTRLEN];  // Broadcast address
    int mtu;  // Maximum Transmission Unit (MTU)
    int is_promiscuous;  // Promiscuous mode status (1: enabled, 0: disabled)
} NetworkInterface;

// Function to retrieve information about available network interfaces
int getNetworkInterfaces(NetworkInterface** interfaces, int* count);

int getPromiscuousMode(const char* interfaceName);

int setPromiscuousMode(const char* interfaceName, int enable);



#endif /* NETWORK_INTERFACE_H */

