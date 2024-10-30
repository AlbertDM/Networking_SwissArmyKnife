src_files = ['main.c', 'socket_manager.h', 'socket_types.h']

if host_machine.system() == 'linux'
    src_files += 'socket_manager_linux.c'
elif host_machine.system() == 'windows'
    src_files += 'socket_manager_windows.c'
    win32_dep = dependency('winsock2')
endif

executable('socket_manager', src_files,
    dependencies: [win32_dep] if host_machine.system() == 'windows' else []
)
