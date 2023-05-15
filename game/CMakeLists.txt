add_subdirectory(Game/)
add_subdirectory(objects/)
add_subdirectory(CollisionHandler/)
add_subdirectory(actions/)
add_subdirectory(assetManager/)
add_subdirectory(cameraTarget/)

target_include_directories(game PUBLIC Game)
target_include_directories(collision_handler PUBLIC CollisionHandler)
target_include_directories(asset_manager PUBLIC assetManager)
target_include_directories(camera_target PUBLIC cameraTarget)

add_subdirectory(playerUserInterface/)
