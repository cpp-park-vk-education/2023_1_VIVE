set(GAME "game")

add_library(${GAME} SHARED game.cpp game.hpp)

target_link_libraries(${GAME} ${SFML_LIBRARIES})
target_link_libraries(${GAME} player tile collision_handler particle particle_set enemy player_user_interface camera_target asset_manager)

