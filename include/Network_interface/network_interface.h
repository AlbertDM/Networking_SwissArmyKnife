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
#define MAC_ADDR_LEN 6  /* 6 Octets in one ethernet addr */

#else   
// Linux Includes and defines.


#include <netinet/in.h>
#include <net/if.h>
#include <net/ethernet.h>
#define INTERFACE_NAME_LENGTH IF_NAMESIZE
#define MAC_ADDR_LEN ETH_ALEN /* 6 Octets in one ethernet addr */

#endif


// Third-party library headers
// #include <some_library.h>



// === Defines === //
//
#define DUPLEX_MODE_LENGTH 8
// IPv4 address size (binary)
#ifndef IPV4_ADDR_LEN
#define IPV4_ADDR_LEN 4
#endif
#define IP_CLASS_LEN 16
#define IP_STRING_LENGTH 46   // Enough for IPv6
#define MAC_ADDRESS_STRLEN 18


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
    uint8_t ip_address[IPV4_ADDR_LEN];  // Array of 4 integers representing the IP address octets
    uint8_t ip_address_aliasing[IPV4_ADDR_LEN];  // Array of 4 integers representing the IP address octets for "IP aliasing"
    // char mac_address[MAC_ADDRESS_STRLEN];    // MAC address
    uint8_t mac_address[MAC_ADDR_LEN];  // Array of 6 integers representing the MAC address bytes
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


/* -------------------- Core Interface Control -------------------- */

// Initialize internal data structures for network interface management
int initNetworkInterface(void);

// Retrieve a list of all network interfaces in the system
int getNetworkInterfaces(NetworkInterface** interfaces, int* count);

// Get promiscuous mode status for a specific interface by index
int getPromiscuousMode(int index, NetworkInterface* interfaces, int count);

// Set promiscuous mode (enable/disable) by index
int setPromiscuousMode(int index, int enable, NetworkInterface* interfaces, int count);

// Set a new name for an interface by index
int setInterfaceName(int index, const char* newName, NetworkInterface* interfaces, int count);

// Set the default gateway for an interface by index
int setDefaultGateway(int index, const char* gatewayAddress, NetworkInterface* interfaces, int count);

// Enable (up = 1) or disable (up = 0) an interface by index
int toggleInterfaceState(int index, int up, NetworkInterface* interfaces, int count);

// Rename an interface at runtime using ioctl (SIOCSIFNAME)
int renameInterface(int index, const char* newName, NetworkInterface* interfaces, int count);

// Get index of an interface by its name from an array of interfaces
int getInterfaceIndexByName(const char* interfaceName, const NetworkInterface* interfaces, int count);


/* -------------------- Static Interface Info -------------------- */

// Get MAC address of an interface
int getMACAddress(int index, const NetworkInterface* interfaces, char* macAddress);

// Get IP address of an interface
int getIPAddress(int index, const NetworkInterface* interfaces, char* ipAddress);

// Get IP class (A, B, C...) of an interface
int getIPClass(int index, const NetworkInterface* interfaces, char* ipClass);

// Get broadcast address of an interface
int getBroadcastAddress(int index, const NetworkInterface* interfaces, char* broadcastAddress);

// Get MTU (Maximum Transmission Unit) of an interface
int getMTU(int index, const NetworkInterface* interfaces, int* mtu);

// Get subnet mask of an interface
int getNetmask(int index, const NetworkInterface* interfaces, char* netmask);

// Get type of interface (Ethernet, loopback, VLAN, etc.)
int getInterfaceType(int index, const NetworkInterface* interfaces, char* type);


/* -------------------- Dynamic Runtime State -------------------- */

// Check if the interface link is up (1) or down (0)
int getLinkStatus(int index, const NetworkInterface* interfaces, int* status);

// Get duplex mode of the interface (half/full)
int getDuplexMode(int index, const NetworkInterface* interfaces, char* mode);

// Get current link speed (in Mbps)
int getCurrentBitrate(int index, const NetworkInterface* interfaces, int* bitrate);


/* -------------------- Statistics and Counters -------------------- */

// Get default gateway address
int getDefaultGateway(int index, const NetworkInterface* interfaces, char* gatewayAddress);

// Get number of link up/down transitions
int getLinkUpDownEvents(int index, const NetworkInterface* interfaces, int* events);

// Get total sent packet count
int getSentPacketCount(int index, const NetworkInterface* interfaces, int* count);

// Get total received packet count
int getReceivedPacketCount(int index, const NetworkInterface* interfaces, int* count);

// Get interface-level error statistics
int getErrorStatistics(int index, const NetworkInterface* interfaces, int* errors);

// Get estimated throughput of the interface
int getInterfaceThroughput(int index, const NetworkInterface* interfaces, int* throughput);

// Get number of dropped packets
int getDroppedPacketsCount(int index, const NetworkInterface* interfaces, int* count);

// Get number of detected Ethernet collisions
int getCollisionCount(int index, const NetworkInterface* interfaces, int* count);

// Get count of receive queue errors (FIFO, overrun, etc.)
int getRXQueueErrors(int index, const NetworkInterface* interfaces, int* count);


/* -------------------- Utility and Conversion -------------------- */

// Convert decimal IP address to dotted format (byte array)
void decimalToIP(int decimalIP, unsigned char* ipAddress);

// Convert dotted IP format to decimal integer
int IPToDecimal(const unsigned char* ipAddress);

// Parse IP string (e.g., "192.168.1.1") into byte array
int parseIPAddress(const char* ipStr, unsigned char* ip);

// Format MAC address as human-readable string (e.g., "aa:bb:cc:dd:ee:ff")
void formatMACAddress(const unsigned char* mac, char* buffer);

// Check if a given interface is a loopback interface
int isLoopbackInterface(const NetworkInterface* iface);




#endif /* NETWORK_INTERFACE_H */

