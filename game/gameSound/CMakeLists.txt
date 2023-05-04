add_subdirectory(ISound/)
add_subdirectory(sound/)

target_include_directories(i_sound PUBLIC ISound)
target_include_directories(sound PUBLIC sound)
