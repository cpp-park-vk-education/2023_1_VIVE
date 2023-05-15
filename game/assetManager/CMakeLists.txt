set(ASSET_MANAGER "asset_manager")

add_library(${ASSET_MANAGER} SHARED asset_manager.cpp asset_manager.hpp)

target_link_libraries(${ASSET_MANAGER} ${SFML_LIBRARIES})
