set(OBJECT "object")

add_library(${OBJECT} SHARED object.cpp object.hpp)

target_link_libraries(${OBJECT} ${SFML_LIBRARIES})
