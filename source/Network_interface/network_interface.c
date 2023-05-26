#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include "network_interface.h"

int get_network_interfaces(NetworkInterface** interfaces, int* count) {
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

            struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
            inet_ntop(AF_INET, &(addr->sin_addr), iface->ip_address, INET6_ADDRSTRLEN);

            // Get IP address class
            unsigned char firstByte = addr->sin_addr.s_addr & 0xFF;
            if (firstByte >= 1 && firstByte <= 126) {
                strncpy(iface->ip_class, "A", sizeof(iface->ip_class));
            } else if (firstByte >= 128 && firstByte <= 191) {
                strncpy(iface->ip_class, "B", sizeof(iface->ip_class));
            } else if (firstByte >= 192 && firstByte <= 223) {
                strncpy(iface->ip_class, "C", sizeof(iface->ip_class));
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
                sprintf(iface->mac_address, "%02X:%02X:%02X:%02X:%02X:%02X",
                        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            } else {
                strcpy(iface->mac_address, "N/A");
            }

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

