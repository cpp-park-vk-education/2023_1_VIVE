add_subdirectory(assetManager/)
add_subdirectory(cameraTarget/)

target_include_directories(asset_manager PUBLIC assetManager)
target_include_directories(camera_target PUBLIC cameraTarget)

add_subdirectory(playerUserInterface/)
