add_library(game STATIC src/game.cpp)

target_include_directories(game PUBLIC include)
target_link_libraries(game state client Player ${SFML_INCLUDE_DIRS})
