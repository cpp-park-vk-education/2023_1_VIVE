set (Settings "settings")

add_library(${Settings} SHARED settings.cpp settings.hpp)

target_link_libraries(${Settings} i_settings)
