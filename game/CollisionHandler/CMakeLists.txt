set(COLLISION_HANDLER "collision_handler")

add_library(${COLLISION_HANDLER} SHARED collision_handler.cpp collision_handler.hpp)

target_link_libraries(${COLLISION_HANDLER} ${SFML_LIBRARIES})
target_link_libraries(${COLLISION_HANDLER} physical_object)

# add_subdirectory(tests/)
