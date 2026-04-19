# Professional CMake for V32F20X Module
# This file is the entry point when the module is loaded via ZEPHYR_MODULES.

# 1. Global include directories for this SoC module
# This ensures that SoC-specific headers (like pinctrl_soc.h) are visible
zephyr_include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

# 2. Add drivers
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../drivers drivers)

# 3. Ensure libraries are linked to zephyr interface
# Link v32f20x_hal before drivers to ensure symbols are resolved
zephyr_library_link_libraries(v32f20x_hal v32f20x_drivers)
