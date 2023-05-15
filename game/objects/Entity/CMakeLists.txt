set(ENTITY "entity")

add_library(${ENTITY} SHARED entity.cpp entity.hpp)

target_link_libraries(${ENTITY} ${SFML_LIBRARIES})
target_link_libraries(${ENTITY} movable_object)
