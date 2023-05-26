project('Ethernet_SwissArmyKnife', 'c')

# Compiler settings, dependencies, and other project-wide configuration

# Include and build the library packages
subdir('source/Network_interface/network_interface')
# subdir('src/package2')
# ...

# Include and build the wrappers (if applicable)
# subdir('wrappers/wrapper1')
# subdir('wrappers/wrapper2')
# ...

# Define targets for unit tests
# unittest_dir = 'tests/unit'
# unit_tests = [
#     'test_package1',
#     'test_package2',
#     # ...
# ]
# foreach test : unit_tests
#   executable(test, files([test + '.c']), include_directories : 'src')
# endforeach
# 
# # Define target for the application tests
# app_tests = [
#     'test1',
#     'test2',
#     # ...
# ]
# foreach test : app_tests
#   executable(test, files([test + '.c']), include_directories : 'src')
# endforeach

# Main library target
library('Ethernet_SwissArmyKnife',
  sources: ['source/Network_interface/network_interface.c'],
  include_directories: ['include/Network_interface'],
  # dependencies: ['dependency1', 'dependency2', ...],
  version: '0.0.1',   # Version number for the library
  soversion: '0',     # Major version number for the library
)

# Executable target
# executable('my_app',
#   sources: ['main.c'],
#   include_directories: ['src/network_interface'],
#   dependencies: ['my_library']
# )
