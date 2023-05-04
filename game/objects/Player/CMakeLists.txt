set(PLAYER "player")

add_library(${PLAYER} SHARED player.cpp player.hpp)

target_link_libraries(${PLAYER} entity)
