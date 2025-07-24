project('socket_manager_test', 'c')

# Compiler-specific flags
cc = meson.get_compiler('c')
host_system = host_machine.system()
c_args = ['-Wall', '-Werror']
c_args += cc.get_supported_arguments(['-std=c99'])

src_files = ['main.c', 'socket_manager.h', 'socket_types.h']

if host_machine.system() == 'linux'
    src_files += 'socket_manager_linux.c'
    dependencies_external = []
elif host_machine.system() == 'windows'
    src_files += 'socket_manager_windows.c'
    win32_dep = dependency('winsock2')
    dependencies_external = [win32_dep]
endif

# Executable
# Bug
# executable('socket_manager', src_files,
#     dependencies: [win32_dep] if host_machine.system() == 'windows' else []
# )
executable('socket_manager', src_files,
   dependencies: dependencies_external) 
