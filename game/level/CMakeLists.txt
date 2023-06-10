aux_source_directory(src level_SRCS)

add_library(level ${level_SRCS})
target_include_directories(level PUBLIC include)
target_link_libraries(level PUBLIC ${SFML_LIBRARIES})
target_link_libraries(level PUBLIC object player tile enemy player_user_interface collision_handler game camera_target sound background boss trigger)
