/**
 * @file network_interface_core.c
 * @brief Core functionality for the Network Interface Library.
 *
 * This file contains the core implementation of the Network Interface Library,
 * providing functions for managing network interfaces, including operations
 * related to promiscuous mode, default gateway, link status, packet counts,
 * error statistics, throughput, and more.
 *
 * @see network_interface.h
 * @see network_interface_info.h
 * @see network_interface_statistics.h
 *
 * @author Albert Domingo Murillo
 * @date 2023/06/06
 * @version 1.0
 * @contact albertdm.engineer@gmail.com
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include "network_interface.h"
// #include "network_interface_info.h"
// #include "network_interface_statistics.h"


#define LOCALHOST_IP 0x7F000001   // 127.0.0.1


/**
 * @brief Get the index of a network interface by name.
 *
 * This function searches for a network interface with the specified name in the provided array
 * of NetworkInterface structures and returns its index.
 *
 * @param interfaceName The name of the interface to search for.
 * @param interfaces The array of NetworkInterface structures.
 * @param count The number of interfaces in the array.
 * @return The index of the interface if found, or -1 if not found.
 */
int getInterfaceIndexByName(const char* interfaceName, const NetworkInterface* interfaces, int count) {
    int index = -1; // Default value indicating interface not found

    // Iterate through the network interfaces array
    for (int i = 0; i < count; i++) {
        if (strcmp(interfaceName, interfaces[i].name) == 0) {
            index = i; // Interface found, assign index
            break;
        }
    }

    return index;
}



/**
 * @brief Retrieve the promiscuous mode status for a network interface.
 *
 * This function retrieves the promiscuous mode status for the network interface
 * at the specified index in the provided array of NetworkInterface structures.
 * It also updates the `is_promiscuous` field in the corresponding structure.
 *
 * @param index The index of the network interface.
 * @param interfaces The array of NetworkInterface structures.
 * @param count The number of interfaces in the array.
 * @return 1 if promiscuous mode is enabled, 0 if it is disabled, or -1 on error.
 */
int getPromiscuousMode(int index, NetworkInterface* interfaces, int count) {
    int sockfd;
    struct ifreq ifr;

    // Create a socket for ioctl operations
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Copy the interface name to the ifreq structure
    strncpy(ifr.ifr_name, interfaces[index].name, IFNAMSIZ);

    // Get the current interface flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("IOCTL failed");
        close(sockfd);
        return -1;
    }

    // Close the socket
    close(sockfd);

    // Determine if promiscuous mode is enabled or disabled based on the IFF_PROMISC flag
    int promiscuousMode = (ifr.ifr_flags & IFF_PROMISC) ? 1 : 0;

    // Update the is_promiscuous field in the corresponding NetworkInterface structure
    interfaces[index].is_promiscuous = promiscuousMode;

    return promiscuousMode;
}



/**
 * @brief Set the promiscuous mode status for a network interface.
 *
 * This function sets the promiscuous mode status for the network interface
 * at the specified index in the provided array of NetworkInterface structures.
 * It also updates the `is_promiscuous` field in the corresponding structure.
 *
 * @param index The index of the network interface.
 * @param interfaces The array of NetworkInterface structures.
 * @param count The number of interfaces in the array.
 * @param enable Flag indicating whether to enable (1) or disable (0) promiscuous mode.
 * @return 0 on success, or -1 on error.
 */
int setPromiscuousMode(int index, NetworkInterface* interfaces, int count, int enable) {
    int sockfd;
    struct ifreq ifr;

    // Create a socket for ioctl operations
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Copy the interface name to the ifreq structure
    strncpy(ifr.ifr_name, interfaces[index].name, IFNAMSIZ);

    // Get the current interface flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("IOCTL failed");
        close(sockfd);
        return -1;
    }

    // Set or clear the IFF_PROMISC flag based on the enable parameter
    if (enable) {
        ifr.ifr_flags |= IFF_PROMISC;  // Enable promiscuous mode
    } else {
        ifr.ifr_flags &= ~IFF_PROMISC;  // Disable promiscuous mode
    }

    // Apply the modified interface flags
    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("IOCTL failed");
        close(sockfd);
        return -1;
    }

    // Close the socket
    close(sockfd);

    // Update the is_promiscuous field in the corresponding NetworkInterface structure
    interfaces[index].is_promiscuous = enable;

    return 0;
}



/**
 * @brief Retrieve information about available network interfaces.
 *
 * This function retrieves information about the available network interfaces
 * on the system. It populates the provided array of NetworkInterface pointers
 * with the details of each interface and updates the value of the count
 * parameter with the total number of interfaces found.
 *
 * @param[out] interfaces Pointer to an array of NetworkInterface pointers
 *                        to store the interface information.
 * @param[out] count      Pointer to an integer to store the number of interfaces.
 * @return 0 on success, or a negative value on failure.
 */
int getNetworkInterfaces (NetworkInterface** interfaces, int* count) {
    struct ifaddrs *ifaddr, *ifa;
    int interfaceCount = 0;

    // Get the list of network interfaces
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return -1;
    }

    // Count the number of network interfaces
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET) {
            interfaceCount++;
        }
    }

    // Allocate memory for the interface array
    *interfaces = (NetworkInterface*)malloc(sizeof(NetworkInterface) * interfaceCount);
    if (*interfaces == NULL) {
        perror("malloc");
        freeifaddrs(ifaddr);
        return -1;
    }

    // Populate the interface array with information
    int index = 0;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET) {
            NetworkInterface* iface = &((*interfaces)[index]);

            strncpy(iface->name, ifa->ifa_name, IF_NAMESIZE - 1);
            iface->name[IF_NAMESIZE - 1] = '\0';

           // Get the IP address
#if 1 
          struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
          uint32_t ip = ntohl(addr->sin_addr.s_addr);
          iface->ip_address[0] = (ip >> 24) & 0xFF;
          iface->ip_address[1] = (ip >> 16) & 0xFF;
          iface->ip_address[2] = (ip >> 8) & 0xFF;
          iface->ip_address[3] = ip & 0xFF;
#else
          struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
          inet_ntop(AF_INET, &(addr->sin_addr), iface->ip_address, INET6_ADDRSTRLEN);
#endif 

            // Get IP address class
            unsigned char firstByte = addr->sin_addr.s_addr & 0xFF;
            if (firstByte >= 1 && firstByte <= 126) {
                strncpy(iface->ip_class, "A", sizeof(iface->ip_class));
            } else if (firstByte >= 128 && firstByte <= 191) {
                strncpy(iface->ip_class, "B", sizeof(iface->ip_class));
            } else if (firstByte >= 192 && firstByte <= 223) {
                strncpy(iface->ip_class, "C", sizeof(iface->ip_class));
            } else if (addr->sin_addr.s_addr == htonl(LOCALHOST_IP)) {
                strncpy(iface->ip_class, "Local host", sizeof(iface->ip_class));
            } else {
                strncpy(iface->ip_class, "Unknown", sizeof(iface->ip_class));
            }

            // Get broadcast address
            struct sockaddr_in* bcast = (struct sockaddr_in*)ifa->ifa_broadaddr;
            if (bcast != NULL) {
                inet_ntop(AF_INET, &(bcast->sin_addr), iface->broadcast_address, INET6_ADDRSTRLEN);
            } else {
                strcpy(iface->broadcast_address, "N/A");
            }

            // Get MAC address
            int sock = socket(AF_INET, SOCK_DGRAM, 0);
            struct ifreq ifreq;
            strncpy(ifreq.ifr_name, ifa->ifa_name, IF_NAMESIZE);
            if (ioctl(sock, SIOCGIFHWADDR, &ifreq) != -1) {
                unsigned char* mac = (unsigned char*)ifreq.ifr_hwaddr.sa_data;
#if 1                 
                for (int i = 0; i < 6; i++) {
                    iface->mac_address[i] = mac[i];
                }
            } else {
                // Set MAC address as all zeros
                memset(iface->mac_address, 0, sizeof(iface->mac_address));
            }

#else
                sprintf(iface->mac_address, "%02X:%02X:%02X:%02X:%02X:%02X",
                        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            } else {
                strcpy(iface->mac_address, "N/A");
            }
#endif

            // Get link status
            struct ifreq ifr;
            int fd = socket(AF_INET, SOCK_DGRAM, 0);
            memset(&ifr, 0, sizeof(ifr));
            strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);
            if (ioctl(fd, SIOCGIFFLAGS, &ifr) != -1) {
                iface->link_status = (ifr.ifr_flags & IFF_UP) ? 1 : 0;
            } else {
                iface->link_status = -1;  // Unknown
            }
            close(fd);

            // Get MTU
            fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (ioctl(fd, SIOCGIFMTU, &ifr) != -1) {
                iface->mtu = ifr.ifr_mtu;
            } else {
                iface->mtu = -1;  // Unknown
            }
            close(fd);

            // Get promiscuous mode status
            fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (ioctl(fd, SIOCGIFFLAGS, &ifr) != -1) {
                iface->is_promiscuous = (ifr.ifr_flags & IFF_PROMISC) ? 1 : 0;
            } else {
                iface->is_promiscuous = -1;  // Unknown
            }
            close(fd);

            index++;
        }
    }

    freeifaddrs(ifaddr);

    *count = interfaceCount;

    return 0;
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

int initNetworkInterface(void) {

  return 0;
}


