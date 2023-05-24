add_subdirectory(iSound)
add_subdirectory(sound)

target_include_directories(i_sound PUBLIC iSound)
target_include_directories(sound PUBLIC sound)
