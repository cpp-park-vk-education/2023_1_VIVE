set(ISettings "i_settings")

add_library(${ISettings} SHARED i_settings.cpp i_settings.hpp)

target_link_libraries(${ISettings} ${SFML_LIBRARIES})