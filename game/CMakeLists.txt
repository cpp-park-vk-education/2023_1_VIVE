add_subdirectory(client)
add_subdirectory(game_engine)
add_subdirectory(level)
add_subdirectory(state)
add_subdirectory(animation)
add_subdirectory(sound)
#add_subdirectory(saving)


add_subdirectory(objects/)
add_subdirectory(CollisionHandler/)
add_subdirectory(actions/)
add_subdirectory(assetManager/)
add_subdirectory(cameraTarget/)
add_subdirectory(playerUserInterface/)

target_include_directories(collision_handler PUBLIC CollisionHandler)
target_include_directories(asset_manager PUBLIC assetManager)
target_include_directories(camera_target PUBLIC cameraTarget)

