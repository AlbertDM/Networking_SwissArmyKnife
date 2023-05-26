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
int getNetworkInterfaces(NetworkInterface** interfaces, int* count) {
    DWORD buffer_size = 0;
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    PIP_ADAPTER_ADDRESSES adapter_addresses = NULL;
    PIP_ADAPTER_ADDRESSES current_adapter = NULL;
    int num_interfaces = 0;

    // Call GetAdaptersAddresses with a null buffer to get the required buffer size
    if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, adapter_addresses, &buffer_size) == ERROR_BUFFER_OVERFLOW) {
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
                            NetworkInterface* nw_if = &((*interfaces)[num_interfaces]);
                            strncpy(nw_if->name, current_adapter->AdapterName, sizeof(nw_if->name));
                            strncpy(nw_if->ip_address, ip_address, sizeof(nw_if->ip_address));
                            nw_if->link_status = (current_adapter->OperStatus == IfOperStatusUp) ? 1 : 0;
                            // Populate other fields as needed
                            // ...

                            num_interfaces++;
                        }

                        unicast_address = unicast_address->Next;
                    }
                }

                current_adapter = current_adapter->Next;
            }
        }
    }

    free(adapter_addresses);
    *count = num_interfaces;

    return 0;
}
