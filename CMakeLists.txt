cmake_minimum_required(VERSION 3.0.0)
project(ATOMIC_GOD)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBRARIES})

add_subdirectory(game/)
target_link_libraries(${PROJECT_NAME} PUBLIC asset_manager camera_target player_user_interface)
