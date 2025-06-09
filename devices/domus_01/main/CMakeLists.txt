set(SOURCES
	domus_01.c
	wifi_manager.c
  mqtt_manager.c
  command_processor.c
  ntp_manager.c
)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS ".")
