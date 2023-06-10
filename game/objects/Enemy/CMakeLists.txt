set(ENEMY "enemy")

add_library(${ENEMY} SHARED enemy.cpp enemy.hpp)

target_link_libraries(${ENEMY} ${SFML_LIBRARIES})
target_link_libraries(${ENEMY} entity particle_set)

# add_subdirectory(tests/)
