set(TILE "tile")

add_library(${TILE} SHARED tile.cpp tile.hpp)

target_link_libraries(${TILE} ${SFML_LIBRARIES})
target_link_libraries(${TILE} physical_object asset_manager)

# add_subdirectory(tests/)
