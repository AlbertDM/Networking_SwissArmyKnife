/**
 * @file network_interface_utils.c
 * @brief Dynamic functionalities for the Network Interface Library.
 *
 * This file contains the dynamic options implementations of the Network Interface Library,
 * providing functions for managing network interfaces, including operations
 * related to promiscuous mode, default gateway, link status, packet counts,
 * error statistics, throughput, and more.
 *
 * @see network_interface.h
 * @see network_interface_dynamic.h
 *
 * @author Albert Domingo Murillo
 * @date 2023/06/06
 * @version 1.0
 * @contact albertdm.engineer@gmail.com
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToIP(int decimalIP, unsigned char* ipAddress) {
    ipAddress[0] = (decimalIP >> 24) & 0xFF;
    ipAddress[1] = (decimalIP >> 16) & 0xFF;
    ipAddress[2] = (decimalIP >> 8) & 0xFF;
    ipAddress[3] = decimalIP & 0xFF;
}

#if 0
int main() {
    int decimalIP = 2130706433;  // Example decimal IP: 127.0.0.1
    unsigned char ipAddress[4];

    decimalToIP(decimalIP, ipAddress);

    printf("Decimal IP: %d.%d.%d.%d\n", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);

    return 0;
}
#endif

int IPToDecimal(const unsigned char* ipAddress) {
    return (ipAddress[0] << 24) | (ipAddress[1] << 16) | (ipAddress[2] << 8) | ipAddress[3];
}

#if 0
int main() {
    unsigned char ipAddress[4] = {127, 0, 0, 1}; // Example IP: 127.0.0.1
    int decimalIP = IPToDecimal(ipAddress);

    printf("Decimal IP: %d\n", decimalIP);

    return 0;
}
#endif



/**
 * @brief Convert a string-formatted IP address to 4-byte format.
 *
 * Parses a string like "192.168.1.1" into an array of 4 bytes.
 *
 * @param ipStr Input string with dotted IP.
 * @param ip Output 4-byte array.
 * @return 0 on success, -1 on failure.
 */
int parseIPAddress(const char* ipStr, unsigned char* ip) {
    // TODO: implement this
    return 0;
}



/**
 * @brief Format a binary MAC address into human-readable form.
 *
 * Converts 6-byte MAC address into "xx:xx:xx:xx:xx:xx" string.
 *
 * @param mac 6-byte MAC address array.
 * @param buffer Output string buffer.
 */
void formatMACAddress(const unsigned char* mac, char* buffer) {
    // TODO: implement this
}



/**
 * @brief Check if the given interface is a loopback interface.
 *
 * This is usually used to skip non-relevant interfaces like 'lo'.
 *
 * @param iface Pointer to the NetworkInterface struct.
 * @return 1 if loopback, 0 otherwise.
 */
int isLoopbackInterface(const NetworkInterface* iface) {
    // TODO: implement this
    return 0;
}
