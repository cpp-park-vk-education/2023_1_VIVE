set(GAME "Game")

include_directories(include)
add_library(${GAME} SHARED src/Game.cpp)
target_include_directories(${GAME} PUBLIC include)

target_link_libraries(${GAME} sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${GAME} Player)

