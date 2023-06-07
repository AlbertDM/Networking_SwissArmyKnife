#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <Ws2tcpip.h>
#include <pcap.h>   // -lpcap
#include "network_interface.h"



/**
 * @brief Get the promiscuous mode status of a network interface.
 *
 * @param interfaceName The name of the network interface.
 * @return The promiscuous mode status (1 if enabled, 0 if disabled) on success, or -1 on failure.
 */
int getPromiscuousMode(const char* interfaceName) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Step 1: Open the adapter
    pcap_t* handle = pcap_open_live(interfaceName, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        printf("Failed to open adapter: %s\n", errbuf);
        return -1;
    }

    // Step 2: Get the promiscuous mode status
    int promiscuousMode = pcap_getnonblock(handle, errbuf);
    if (promiscuousMode == -1) {
        printf("Failed to get promiscuous mode status: %s\n", errbuf);
        pcap_close(handle);
        return -1;
    }

    // Step 3: Print the promiscuous mode status
    printf("Promiscuous Mode: %s\n", promiscuousMode ? "Enabled" : "Disabled");

    // Step 4: Close the adapter
    pcap_close(handle);

    return 0;
}


/**
 * @brief Set the promiscuous mode of a network interface.
 *
 * @param interfaceName The name of the network interface.
 * @param enable Flag indicating whether to enable (1) or disable (0) promiscuous mode.
 * @return 0 on success, or -1 on failure.
 */
int setPromiscuousMode(const char* interfaceName, int enable) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Step 1: Open the adapter
    pcap_t* handle = pcap_open_live(interfaceName, BUFSIZ, enable, 1000, errbuf);
    if (handle == NULL) {
        printf("Failed to open adapter: %s\n", errbuf);
        return -1;
    }

    // Step 2: Set the promiscuous mode
    int result = pcap_setnonblock(handle, enable, errbuf);
    if (result == -1) {
        printf("Failed to set promiscuous mode: %s\n", errbuf);
        pcap_close(handle);
        return -1;
    }

    // Step 3: Print the promiscuous mode status
    printf("Promiscuous Mode: %s\n", enable ? "Enabled" : "Disabled");

    // Step 4: Close the adapter
    pcap_close(handle);

    return 0;
}


/**
 * @brief Get a list of network interfaces and their information.
 *
 * @param interfaces Pointer to an array of NetworkInterface structures to be filled.
 * @param count Pointer to an integer to store the number of network interfaces found.
 * @return 0 on success, or -1 on failure.
 */
#if 0
int getNetworkInterfaces(NetworkInterface** interfaces, int* count) {
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG buffer_size = 0;
    PIP_ADAPTER_ADDRESSES adapter_addresses = NULL;
    PIP_ADAPTER_ADDRESSES current_adapter = NULL;
    int num_interfaces = 0;
    int result = -1;

    printf("\n Version 7June 9:11\n");

    // Call GetAdaptersAddresses with a null buffer to get the required buffer size
    if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, NULL, &buffer_size) == ERROR_BUFFER_OVERFLOW) {
        adapter_addresses = (PIP_ADAPTER_ADDRESSES)malloc(buffer_size);
        if (adapter_addresses == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return -1;
        }

        // Call GetAdaptersAddresses again with the allocated buffer
        if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, adapter_addresses, &buffer_size) == NO_ERROR) {
            current_adapter = adapter_addresses;
            while (current_adapter) {
                if (current_adapter->OperStatus == IfOperStatusUp) {
                    IP_ADAPTER_UNICAST_ADDRESS* unicast_address = current_adapter->FirstUnicastAddress;
                    while (unicast_address) {
                        // Retrieve the IP address in string format
                        char ip_address[INET6_ADDRSTRLEN];
                        DWORD ip_address_length = sizeof(ip_address);
                        if (WSAAddressToStringA(unicast_address->Address.lpSockaddr, unicast_address->Address.iSockaddrLength, NULL, ip_address, &ip_address_length) == 0) {
                            // Add the interface to the list
                            NetworkInterface* nw_if = (NetworkInterface*)realloc(*interfaces, (num_interfaces + 1) * sizeof(NetworkInterface));
                            if (nw_if == NULL) {
                                fprintf(stderr, "Memory allocation error\n");
                                result = -1;
                                goto cleanup;
                            }
                            *interfaces = nw_if;

                            // Populate the interface information
                            NetworkInterface* current_interface = &(*interfaces)[num_interfaces];
                            strncpy(current_interface->name, current_adapter->AdapterName, sizeof(current_interface->name));
                            strncpy(current_interface->ip_address, ip_address, sizeof(current_interface->ip_address));
                            current_interface->link_status = 1; // Assume link is up
                            // Populate other fields as needed
                            // ...

                            num_interfaces++;
                        }

                        unicast_address = unicast_address->Next;
                    }
                }

                current_adapter = current_adapter->Next;
            }

            result = 0; // Success
        } else {
            fprintf(stderr, "Error retrieving adapter addresses\n");
            result = -1;
        }
    } else {
        fprintf(stderr, "Error retrieving adapter addresses buffer size\n");
        result = -1;
    }

cleanup:
    free(adapter_addresses);
    *count = num_interfaces;

    return result;
}


#else

// Link with Iphlpapi.lib
// #pragma comment(lib, "IPHLPAPI.lib")

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

int getNetworkInterfaces(NetworkInterface** interfaces, int* count) {

    /* Declare and initialize variables */

    // DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    unsigned int i = 0;

    // Set the flags to pass to GetAdaptersAddresses
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    // default to unspecified address family (both)
    ULONG family = AF_UNSPEC;

    LPVOID lpMsgBuf = NULL;

    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG outBufLen = 0;
    ULONG Iterations = 0;

    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
    PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
    PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
    IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
    IP_ADAPTER_PREFIX *pPrefix = NULL;

/*
    if (argc != 2) {
        printf(" Usage: getadapteraddresses family\n");
        printf("        getadapteraddresses 4 (for IPv4)\n");
        printf("        getadapteraddresses 6 (for IPv6)\n");
        printf("        getadapteraddresses A (for both IPv4 and IPv6)\n");
        exit(1);
    }

    if (atoi(argv[1]) == 4)
        family = AF_INET;
    else if (atoi(argv[1]) == 6)
        family = AF_INET6;
*/      family = AF_INET;

    printf("Calling GetAdaptersAddresses function with family = ");
    if (family == AF_INET)
        printf("AF_INET\n");
    if (family == AF_INET6)
        printf("AF_INET6\n");
    if (family == AF_UNSPEC)
        printf("AF_UNSPEC\n\n");

    // Allocate a 15 KB buffer to start with.
    outBufLen = WORKING_BUFFER_SIZE;

    do {

        pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(outBufLen);
        if (pAddresses == NULL) {
            printf
                ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
            exit(1);
        }

        dwRetVal =
            GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

        if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
            FREE(pAddresses);
            pAddresses = NULL;
        } else {
            break;
        }

        Iterations++;

    } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

    if (dwRetVal == NO_ERROR) {
        // If successful, output some information from the data we received
        pCurrAddresses = pAddresses;
        while (pCurrAddresses) {
            printf("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n",
                   pCurrAddresses->Length);
            printf("\tIfIndex (IPv4 interface): %lu\n", pCurrAddresses->IfIndex);
            printf("\tAdapter name: %s\n", pCurrAddresses->AdapterName);

            pUnicast = pCurrAddresses->FirstUnicastAddress;
            if (pUnicast != NULL) {
                for (i = 0; pUnicast != NULL; i++)
                    pUnicast = pUnicast->Next;
                printf("\tNumber of Unicast Addresses: %d\n", i);
            } else
                printf("\tNo Unicast Addresses\n");

            pAnycast = pCurrAddresses->FirstAnycastAddress;
            if (pAnycast) {
                for (i = 0; pAnycast != NULL; i++)
                    pAnycast = pAnycast->Next;
                printf("\tNumber of Anycast Addresses: %d\n", i);
            } else
                printf("\tNo Anycast Addresses\n");

            pMulticast = pCurrAddresses->FirstMulticastAddress;
            if (pMulticast) {
                for (i = 0; pMulticast != NULL; i++)
                    pMulticast = pMulticast->Next;
                printf("\tNumber of Multicast Addresses: %d\n", i);
            } else
                printf("\tNo Multicast Addresses\n");

            pDnServer = pCurrAddresses->FirstDnsServerAddress;
            if (pDnServer) {
                for (i = 0; pDnServer != NULL; i++)
                    pDnServer = pDnServer->Next;
                printf("\tNumber of DNS Server Addresses: %d\n", i);
            } else
                printf("\tNo DNS Server Addresses\n");

            printf("\tDNS Suffix: %S\n", pCurrAddresses->DnsSuffix);
            printf("\tDescription: %S\n", pCurrAddresses->Description);
            printf("\tFriendly name: %S\n", pCurrAddresses->FriendlyName);

            if (pCurrAddresses->PhysicalAddressLength != 0) {
                printf("\tPhysical address: ");
                for (i = 0; i < (int) pCurrAddresses->PhysicalAddressLength;
                     i++) {
                    if (i == (pCurrAddresses->PhysicalAddressLength - 1))
                        printf("%.2X\n",
                               (int) pCurrAddresses->PhysicalAddress[i]);
                    else
                        printf("%.2X-",
                               (int) pCurrAddresses->PhysicalAddress[i]);
                }
            }
            printf("\tFlags: %ld\n", pCurrAddresses->Flags);
            printf("\tMtu: %lu\n", pCurrAddresses->Mtu);
            printf("\tIfType: %ld\n", pCurrAddresses->IfType);
            printf("\tOperStatus: %d\n", pCurrAddresses->OperStatus);
            printf("\tIpv6IfIndex (IPv6 interface): %lu\n",
                   pCurrAddresses->Ipv6IfIndex);
            printf("\tZoneIndices (hex): ");
            for (i = 0; i < 16; i++)
                printf("%lx ", pCurrAddresses->ZoneIndices[i]);
            printf("\n");

            printf("\tTransmit link speed: %I64llu\n", pCurrAddresses->TransmitLinkSpeed);
            printf("\tReceive link speed: %I64llu\n", pCurrAddresses->ReceiveLinkSpeed);

            pPrefix = pCurrAddresses->FirstPrefix;
            if (pPrefix) {
                for (i = 0; pPrefix != NULL; i++)
                    pPrefix = pPrefix->Next;
                printf("\tNumber of IP Adapter Prefix entries: %d\n", i);
            } else
                printf("\tNumber of IP Adapter Prefix entries: 0\n");

            printf("\n");

            pCurrAddresses = pCurrAddresses->Next;
        }
    } else {
        printf("Call to GetAdaptersAddresses failed with error: %ld\n",
               dwRetVal);
        if (dwRetVal == ERROR_NO_DATA)
            printf("\tNo addresses were found for the requested parameters\n");
        else {

            if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                    NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
                    // Default language
                    (LPTSTR) & lpMsgBuf, 0, NULL)) {
                printf("\tError: %p", lpMsgBuf);
                LocalFree(lpMsgBuf);
                if (pAddresses)
                    FREE(pAddresses);
                exit(1);
            }
        }
    }

    if (pAddresses) {
        FREE(pAddresses);
    }

    return 0;
}
#endif