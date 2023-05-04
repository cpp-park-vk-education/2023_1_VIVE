set(navigationIcons "i_navigation_icons")

add_library(${navigationIcons} SHARED i_navigation_icons.cpp i_navigation_icons.hpp)

target_link_libraries(${navigationIcons} ${SFML_LIBRARIES})
