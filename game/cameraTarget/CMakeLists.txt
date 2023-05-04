add_subdirectory(ICamera/)
add_subdirectory(camera/)

target_include_directories(i_camera PUBLIC ICamera)
target_include_directories(camera PUBLIC camera)
