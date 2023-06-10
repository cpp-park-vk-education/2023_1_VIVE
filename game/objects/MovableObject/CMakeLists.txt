set(MOVABLE_OBJECT "movable_object")

add_library(${MOVABLE_OBJECT} SHARED movable_object.cpp movable_object.hpp)

target_link_libraries(${MOVABLE_OBJECT} ${SFML_LIBRARIES})
target_link_libraries(${MOVABLE_OBJECT} physical_object animation)
