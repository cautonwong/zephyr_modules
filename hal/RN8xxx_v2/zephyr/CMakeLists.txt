zephyr_library()

zephyr_library_sources(src/system_rn831x_rn861x_mcu.c)
zephyr_library_sources(src/cpu_rn8318.c)
# Add other sources as needed

zephyr_library_include_directories(lib)
zephyr_library_include_directories(src)

# Link the precompiled library
zephyr_library_link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/../lib/rn8xxx_v2_lib.a)
