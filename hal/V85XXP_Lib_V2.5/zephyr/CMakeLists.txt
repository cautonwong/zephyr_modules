zephyr_library()

zephyr_include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/CMSIS_Include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/Lib_Driver/inc
)

file(GLOB v85xxp_hal_src
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/Lib_Driver/src/*.c
)

# Keep Zephyr's uart_v85xxp as the active UART implementation.
list(FILTER v85xxp_hal_src EXCLUDE REGEX ".*/lib_uart\\.c$")

zephyr_library_sources(${v85xxp_hal_src})
