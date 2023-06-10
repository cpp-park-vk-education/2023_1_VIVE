set(PARTICLE_SET "particle_set")

add_library(${PARTICLE_SET} SHARED particle_set.cpp particle_set.hpp)

target_link_libraries(${PARTICLE_SET} ${SFML_LIBRARIES})
target_link_libraries(${PARTICLE_SET} particle)

# add_subdirectory(tests/)
