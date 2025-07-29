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
#ifndef IPV4_ADDR_LEN
#define IPV4_ADDR_LEN 4   // IPv4 address size (binary)
#endif
#ifndef INTERFACE_NAME_LENGTH
#define INTERFACE_NAME_LENGTH 64
#endif
#define DRIVER_NAME_LENGTH 32
#define DUPLEX_MODE_LENGTH 8
#define INTERFACE_TYPE_LENGTH 16
#define IP_CLASS_LEN 16
#define IP_STRING_LENGTH 46   // Enough for IPv6
#define MAC_ADDRESS_STRLEN 18
#define PCI_DEVICE_LENGTH 32


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

typedef struct {
    uint8_t ip[IPV4_ADDR_LEN];              // IPv4 address
    uint8_t alias[IPV4_ADDR_LEN];           // Alias address (if any)
    char broadcast[IP_STRING_LENGTH];       // Broadcast address
    char gateway[IP_STRING_LENGTH];         // Default gateway
    int mtu;                                // Maximum Transmission Unit
} InterfaceAddressInfo;

typedef struct {
    int link_status;                        // 1 = up, 0 = down
    int is_promiscuous;                     // 1 = enabled, 0 = disabled
    int speed_mbps;                         // Negotiated speed
    char duplex_mode[DUPLEX_MODE_LENGTH];   // "full" or "half"
    int vlan_id;                            // VLAN ID (if tagged)
    int tx_queue_len;                       // TX queue length
    int num_rx_queues;                      // Number of RX queues
} InterfaceLinkInfo;

typedef struct {
    int packets_sent;
    int packets_received;
    int errors;
    int dropped;
    int collisions;
    int throughput_kbps;                    // Computed from stats
} InterfaceStats;

typedef struct {
    float latency_ms;
    float jitter_ms;
    float packet_loss_pct;
    int qos_priority;                       // DSCP or other tag
} InterfaceQoS;

typedef struct {
    char name[INTERFACE_NAME_LENGTH];             // Interface name (e.g. eth0)
    uint8_t mac[MAC_ADDR_LEN];                    // MAC address (binary format)
    char interface_type[INTERFACE_TYPE_LENGTH];   // "ethernet", "loopback", etc.
    char driver_name[DRIVER_NAME_LENGTH];         // e.g. "e1000e", "ixgbe"
    char pci_device[PCI_DEVICE_LENGTH];           // PCI bus info (Linux)

    InterfaceAddressInfo addr;
    InterfaceLinkInfo link;
    InterfaceStats stats;
    InterfaceQoS qos;
} NetworkInterface;



// Enum definition
//
//



// === Function Signatures === //


/* -------------------- Core Interface Control -------------------- */

// Initialize internal data structures for network interface management
int initNetworkInterface(void);

// Checks for common invalid arguments (NULL interfaces, out-of-bounds index).
int check_interface_arguments(const NetworkInterface* interfaces, int index, int count, const char* function_name);

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

