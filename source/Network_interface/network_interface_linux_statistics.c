/**
 * @file network_interface_statistics.c
 * @brief statistics functionalities for the Network Interface Library.
 *
 * This file contains the statistics options implementations of the Network Interface Library,
 * providing functions for managing network interfaces, including operations
 * related to promiscuous mode, default gateway, link status, packet counts,
 * error statistics, throughput, and more.
 *
 * @see network_interface.h
 * @see network_interface_statistics.h
 *
 * @author Albert Domingo Murillo
 * @date 2023/06/06
 * @version 1.0
 * @contact albertdm.engineer@gmail.com
 */

#include "network_interface.h"
#include <stdio.h>
#include <stdlib.h>

int getDefaultGateway(int index, const NetworkInterface* interfaces, char* gatewayAddress) {
    // Implementation of getDefaultGateway
}

int getLinkUpDownEvents(int index, const NetworkInterface* interfaces, int* events) {
    // Implementation of getLinkUpDownEvents
}

int getSentPacketCount(int index, const NetworkInterface* interfaces, int* count) {
    // Implementation of getSentPacketCount
}

int getReceivedPacketCount(int index, const NetworkInterface* interfaces, int* count) {
    // Implementation of getReceivedPacketCount
}

int getErrorStatistics(int index, const NetworkInterface* interfaces, int* errors) {
    // Implementation of getErrorStatistics
}

int getInterfaceThroughput(int index, const NetworkInterface* interfaces, int* throughput) {
    // Implementation of getInterfaceThroughput
}


// ... other statistics functions

