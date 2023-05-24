# Ethernet_SwissArmyKnife

When creating a library in C to work with Ethernet interfaces, here are some ideas for the functionality the library could provide:

1. Interface Enumeration: The library can provide functions to enumerate and retrieve information about available network interfaces, such as their names, IP addresses, MAC addresses, and link status.

2. Packet Capture: Implement functionality to capture Ethernet packets from a specific interface or all interfaces. This could involve setting up a packet capture mechanism using mechanisms like libpcap or raw sockets to capture and process incoming and outgoing Ethernet frames.

3. Packet Injection: Allow the library users to inject Ethernet packets into the network by providing functions to construct Ethernet frames with custom payload and destination/source MAC addresses, and then send them through the appropriate interface.

4. Link Monitoring: Provide capabilities to monitor link status changes for Ethernet interfaces, such as detecting link up/down events and notifying the application when these events occur.

5. Statistics Gathering: Include functions to collect network statistics, such as the number of sent/received packets, error statistics, and interface throughput.

6. VLAN Tagging: Support for working with VLAN (Virtual LAN) tags, including functions to add, remove, or modify VLAN tags on Ethernet frames.

7. Promiscuous Mode: Allow the library to enable or disable promiscuous mode on network interfaces, enabling the capture of all packets on the network, regardless of the destination MAC address.

8. Frame Parsing and Analysis: Implement functions to parse Ethernet frames, extract information from various protocol layers (e.g., IP, TCP, UDP), and provide a higher-level abstraction for packet analysis.

9. Network Configuration: Provide functions to configure network-related settings, such as setting IP addresses, netmasks, and default gateways on interfaces.

10. Multicast Support: Include functions for joining and leaving multicast groups on Ethernet interfaces, enabling multicast packet reception.

These are just some ideas to get you started when creating a library to work with Ethernet interfaces. The specific features and functionality you choose to include will depend on the goals and requirements of your project.


----

ADM Features:
* Several EthIF under the same subnet. (e.g. 192.168.0.XX) internal IP tables.
* Provide information about the IP address and the MAC address. Class, etc...
* DPDK
* eBPF
* io_uring
* Python Wrapper
* application tests in Python
