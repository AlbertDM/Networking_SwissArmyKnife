#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

// === Documentation === //

/**
 * @brief This is a brief description of the header file.
 *
 * This is a more detailed description of the header file.
 * It provides an overview of the purpose and functionality of the contents.
 *
 * @file my_header_file.h
 */


// === Includes === //
//
// System headers
#include <stdio.h>
#include <stdlib.h>

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

// Third-party library headers
// #include <some_library.h>



// === Defines === //
//
#define MAC_ADDRESS_STRLEN 18
#define IP_CLASS_LEN 16


// === Global Variables === //
//
// extern int globalVariable;

// === Macros === //
//
// #define MY_MACRO(x) ((x) * 2)

// === Constants === //
//
//const int MY_CONSTANT;


// === Type Definitions === //
//

// Structure to hold information about a network interface.
typedef struct {
    char name[INTERFACE_NAME_LENGTH];        // Interface name
    // char ip_address[INET6_ADDRSTRLEN];       // IP address
    uint8_t ip_address[4];  // Array of 4 integers representing the IP address octets
    // char mac_address[MAC_ADDRESS_STRLEN];    // MAC address
    uint8_t mac_address[6];  // Array of 6 integers representing the MAC address bytes
    int link_status;                         // Link status (1: up, 0: down)
    char ip_class[IP_CLASS_LEN];             // IP address class (e.g., A, B, C)
    char broadcast_address[INET6_ADDRSTRLEN]; // Broadcast address
    int mtu;                                 // Maximum Transmission Unit (MTU)
    int is_promiscuous;                      // Promiscuous mode status (1: enabled, 0: disabled)
    char default_gateway[INET6_ADDRSTRLEN];   // Default gateway IP address

    // Additional fields for deep analysis of the network interface
    int link_up_down_events;                 // Number of link up/down events
    int packets_sent;                        // Number of sent packets
    int packets_received;                    // Number of received packets
    int error_statistics;                    // Error statistics
    int interface_throughput;                // Interface throughput

    // Add more fields for further analysis as needed
    // ...
    // Network latency measurements
    // Jitter measurements
    // Packet loss statistics
    // Quality of Service (QoS) parameters
    // Bandwidth utilization
    // Network protocol information (e.g., TCP, UDP)
} NetworkInterface;

// Enum definition
//
//



// === Function Signatures === //
//

// Function to retrieve information about available network interfaces
int initNetworkInterface(void);

// Function to retrieve information about available network interfaces
int getNetworkInterfaces(NetworkInterface** interfaces, int* count);


#if 0
// Function to retrieve information about promiscuous mode for a network interfaces
int getPromiscuousMode(const char* interfaceName);

// Function to set promiscuous mode for a network interfaces
int setPromiscuousMode(const char* interfaceName, int enable);

// Function to retrieve information about the default gateway for a network interface
int getDefaultGateway(const char* interfaceName, char* gatewayAddress);

// Function to retrieve the number of link up/down events for a network interface
int getLinkUpDownEvents(const char* interfaceName, int* events);

// Function to retrieve the number of sent packets for a network interface
int getSentPacketCount(const char* interfaceName, int* count);

// Function to retrieve the number of received packets for a network interface
int getReceivedPacketCount(const char* interfaceName, int* count);

// Function to retrieve error statistics for a network interface
int getErrorStatistics(const char* interfaceName, int* errors);

// Function to retrieve the throughput of a network interface
int getInterfaceThroughput(const char* interfaceName, int* throughput);

// Function to set the default gateway for a network interface
int setDefaultGateway(const char* interfaceName, const char* gatewayAddress);

// Function to set the name a network interface
int setInterfaceName(int index, const char* newName, NetworkInterface* interfaces, int count) {

// Function to enable or disable promiscuous mode for a network interface
int setPromiscuousMode(const char* interfaceName, int enable);

// Function to get the IP class (A, B, C) of a network interface
int getIPClass(const char* interfaceName, char* ipClass);

// Function to get the broadcast address of a network interface
int getBroadcastAddress(const char* interfaceName, char* broadcastAddress);

// Function to get the maximum transmission unit (MTU) of a network interface
int getMTU(const char* interfaceName, int* mtu);

// Function to retrieve the MAC address of a network interface
int getMACAddress(const char* interfaceName, char* macAddress);

// Function to retrieve the IP address of a network interface
int getIPAddress(const char* interfaceName, char* ipAddress);

// Function to retrieve the link status (up/down) of a network interface
int getLinkStatus(const char* interfaceName, int* status);
#endif 

// Function to get the index of a network interface by name
int getInterfaceIndexByName(const char* interfaceName, const NetworkInterface* interfaces, int count);

// Function to retrieve information about promiscuous mode for a network interface
int getPromiscuousMode(int index, const NetworkInterface* interfaces, int count);

// Function to set promiscuous mode for a network interface
int setPromiscuousMode(int index, int enable, NetworkInterface* interfaces, int count);

// Function to retrieve information about the default gateway for a network interface
int getDefaultGateway(int index, const NetworkInterface* interfaces, char* gatewayAddress);

// Function to retrieve the number of link up/down events for a network interface
int getLinkUpDownEvents(int index, const NetworkInterface* interfaces, int* events);

// Function to retrieve the number of sent packets for a network interface
int getSentPacketCount(int index, const NetworkInterface* interfaces, int* count);

// Function to retrieve the number of received packets for a network interface
int getReceivedPacketCount(int index, const NetworkInterface* interfaces, int* count);

// Function to retrieve error statistics for a network interface
int getErrorStatistics(int index, const NetworkInterface* interfaces, int* errors);

// Function to retrieve the throughput of a network interface
int getInterfaceThroughput(int index, const NetworkInterface* interfaces, int* throughput);

// Function to set the default gateway for a network interface
int setDefaultGateway(int index, const char* gatewayAddress, NetworkInterface* interfaces, int count);

// Function to set the name of a network interface
int setInterfaceName(int index, const char* newName, NetworkInterface* interfaces, int count);

// Function to enable or disable promiscuous mode for a network interface
int setPromiscuousMode(int index, int enable, NetworkInterface* interfaces, int count);

// Function to get the IP class (A, B, C) of a network interface
int getIPClass(int index, const NetworkInterface* interfaces, char* ipClass);

// Function to get the broadcast address of a network interface
int getBroadcastAddress(int index, const NetworkInterface* interfaces, char* broadcastAddress);

// Function to get the maximum transmission unit (MTU) of a network interface
int getMTU(int index, const NetworkInterface* interfaces, int* mtu);

// Function to retrieve the MAC address of a network interface
int getMACAddress(int index, const NetworkInterface* interfaces, char* macAddress);

// Function to retrieve the IP address of a network interface
int getIPAddress(int index, const NetworkInterface* interfaces, char* ipAddress);

// Function to retrieve the link status (up/down) of a network interface
int getLinkStatus(int index, const NetworkInterface* interfaces, int* status);


#endif /* NETWORK_INTERFACE_H */

