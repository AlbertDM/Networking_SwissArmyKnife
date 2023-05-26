# Networking_SwissArmyKnife

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

Investigate about:
* Zero-Copy and DMA.
* Receive Side Scaling
* BPF vs eBPF
* PF_RING


### io_uring vs PF_RING


PF_RING and io_uring are two different technologies that serve different purposes in the realm of networking and I/O operations. Here's a comparison between the two:

PF_RING:
1. Purpose: PF_RING focuses on high-speed packet capture, processing, and analysis in network applications.
2. Features: It provides efficient packet capture, scaling across multiple CPU cores and network interfaces, packet filtering and classification, packet timestamping, and integration with other tools.
3. Use Cases: PF_RING is commonly used in network monitoring, traffic analysis, intrusion detection and prevention systems, and performance monitoring.
4. Operating System Support: PF_RING is available for Linux, FreeBSD, and Windows.

io_uring:
1. Purpose: io_uring is an I/O interface for asynchronous and efficient I/O operations, including file I/O and network socket operations.
2. Features: It provides high-performance asynchronous I/O, reducing CPU overhead and improving scalability compared to traditional synchronous I/O methods. It supports various types of I/O operations, including read, write, accept, and connect.
3. Use Cases: io_uring is useful in applications that require high-performance I/O operations, such as web servers, databases, and file systems.
4. Operating System Support: io_uring is primarily available on Linux systems.

Key Differences:
1. Focus: PF_RING primarily focuses on network packet capture and analysis, while io_uring is a more general-purpose I/O interface for efficient I/O operations.
2. Scope: PF_RING is specifically designed for high-speed packet processing, including features like packet filtering and timestamping. io_uring, on the other hand, is a broader I/O interface covering various types of I/O operations.
3. Application Domain: PF_RING is commonly used in network monitoring and analysis applications, while io_uring is applicable to a wider range of applications involving I/O operations.
4. Operating System Support: PF_RING is available on Linux, FreeBSD, and Windows, while io_uring is primarily supported on Linux systems.

In summary, PF_RING and io_uring have different focuses and serve different purposes. PF_RING specializes in high-speed packet capture and analysis, while io_uring is an I/O interface for efficient asynchronous I/O operations. The choice between the two depends on the specific requirements of your application, whether it's more network-centric or requires efficient I/O operations in a broader context.

