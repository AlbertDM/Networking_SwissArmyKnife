project('network_interface_test', 'c')

# Compiler-specific flags
cc = meson.get_compiler('c')
host_system = host_machine.system()
c_args = ['-Wall', '-Werror']
c_args += cc.get_supported_arguments(['-std=c99'])

# Source files
sources = ['network_interface_testApp.c']
# if meson_host_machine().startswith('windows')
if host_system == 'windows'
    sources += ['network_interface_windows.c']
    # dependencies_external = ['ws2_32', 'iphlpapi', 'wpcap']
    c_args += ['-D_WIN32_WINNT=0x0600', '-lws2_32'] 
    dependencies_external = [
        cc.find_library('ws2_32'),
        cc.find_library('iphlpapi'),
        cc.find_library('pcap')
    ]
    # dependencies_external = dependencies_external.split()


else
    c_args += ['-D_GNU_SOURCE']
    sources += ['network_interface_linux.c']
    dependencies_external = ['pcap']
endif

# Executable
executable('network_interface_testApp', sources, c_args: c_args, include_directories: '..\..\include\Network_interface', dependencies: dependencies_external)

# Network interface library
network_interface_lib = static_library('network_interface', sources, c_args: c_args, include_directories: '../../include/Network_interface', dependencies: dependencies_external)

