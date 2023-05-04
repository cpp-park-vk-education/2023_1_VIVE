set(BOSS "boss")

add_library(${BOSS} SHARED boss.cpp boss.hpp)

target_link_libraries(${BOSS} entity particle_set)
