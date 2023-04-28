add_subdirectory(Game)
add_subdirectory(Menu)
add_subdirectory(Button)

target_include_directories(game PUBLIC Game)
target_include_directories(menu PUBLIC Menu)
target_include_directories(button PUBLIC Button)
