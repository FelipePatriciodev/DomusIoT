set(SOURCES
	domus_01.c
	wifi_manager.c
)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS ".")
