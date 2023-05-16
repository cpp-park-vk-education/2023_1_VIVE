add_library(game src/game.cpp)

target_include_directories(game PUBLIC include)
target_link_libraries(game state client Player messages ${SFML_LIBRARIES} ${Protobuf_LIBRARIES})
