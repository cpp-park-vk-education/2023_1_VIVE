set(BACKGROUND "background")

add_library(${BACKGROUND} SHARED background.cpp background.hpp)

target_link_libraries(${BACKGROUND} ${SFML_LIBRARIES})
target_link_libraries(${BACKGROUND} object asset_manager)
