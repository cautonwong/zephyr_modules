zephyr_library()
zephyr_library_sources(soc.c)

# If the HAL module is available, include its headers
# zephyr_library_include_directories(${ZEPHYR_RN8XXX_HAL_MODULE_DIR}/include)
