set(PHYSICAL_OBJECT "physical_object")

add_library(${PHYSICAL_OBJECT} SHARED physical_object.cpp physical_object.hpp)

target_link_libraries(${PHYSICAL_OBJECT} ${SFML_LIBRARIES})
target_link_libraries(${PHYSICAL_OBJECT} object hit_box sound)
