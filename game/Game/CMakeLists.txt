add_library(game SHARED Game.cpp Game.hpp)

target_link_libraries(game menu Player ${SFML_INCLUDE_DIRS})
