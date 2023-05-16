set(PARTICLE "particle")

add_library(${PARTICLE} SHARED particle.cpp particle.hpp)

target_link_libraries(${PARTICLE} ${SFML_LIBRARIES})
target_link_libraries(${PARTICLE} movable_object)

# add_subdirectory(tests/)
