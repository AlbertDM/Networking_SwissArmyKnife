$env:CHERE_INVOKING = 'yes'
$env:MSYSTEM = 'MINGW64'

meson setup --wipe build
meson setup build
cd build
ninja   
# ninja test
ninja install