zephyr_library()
zephyr_library_sources_ifdef(CONFIG_WDT_V85XXP wdt_v85xxp.c)
