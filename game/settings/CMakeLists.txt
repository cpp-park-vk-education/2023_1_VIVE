add_subdirectory(ISettings/)
add_subdirectory(settings/)

target_include_directories(i_settings PUBLIC ISettings)
target_include_directories(settings PUBLIC settings)
