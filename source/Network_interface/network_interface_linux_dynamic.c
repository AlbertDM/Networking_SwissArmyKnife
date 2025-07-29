/**
 * @file network_interface_dynamic.c
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


/*
* Network Interface Dynamic (e.g., network_interface_dynamic.c):

This file will contain functions that retrieve dynamic information from the network interface in real-time using sockets or other live data sources.
Functions that can be included in this file:
getPromiscuousMode (to retrieve the promiscuous mode status for a network interface)
*/

/**
 * @brief Get the duplex mode of a network interface.
 *
 * Returns full or half duplex.
 *
 * @param index Index of the interface.
 * @param interfaces Array of NetworkInterface structures.
 * @param mode Output buffer for duplex mode (e.g., "full", "half").
 * @return 0 on success, -1 on failure.
 */
int getDuplexMode(int index, const NetworkInterface* interfaces, char* mode) {
    // TODO: implement this
    return 0;
}

/**
 * @brief Get the current link speed (bitrate) of a network interface.
 *
 * Returns the negotiated link speed in Mbps.
 *
 * @param index Index of the interface.
 * @param interfaces Array of NetworkInterface structures.
 * @param bitrate Pointer to store the bitrate.
 * @return 0 on success, -1 on failure.
 */
int getCurrentBitrate(int index, const NetworkInterface* interfaces, int* bitrate) {
    // TODO: implement this
    return 0;
}
