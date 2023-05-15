add_subdirectory(Game/)
add_subdirectory(objects/)
add_subdirectory(CollisionHandler/)
add_subdirectory(actions/)

target_include_directories(game PUBLIC Game)
target_include_directories(collision_handler PUBLIC CollisionHandler)
