set(NAVIGATION_ICONS "navigation_icons")

add_library(${NAVIGATION_ICONS} SHARED navigation_icons.cpp navigation_icons.hpp)

target_link_libraries(${NAVIGATION_ICONS} ${SFML_LIBRARIES})
target_link_libraries(${NAVIGATION_ICONS} asset_manager)
