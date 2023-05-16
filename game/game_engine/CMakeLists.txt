add_library(game src/game.cpp)

target_include_directories(game PUBLIC include)
target_link_libraries(game state client player messages ${SFML_LIBRARIES} ${Protobuf_LIBRARIES} camera_target player_user_interface enemy tile collision_handler)
