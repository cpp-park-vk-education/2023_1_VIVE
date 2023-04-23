cmake_minimum_required(VERSION 3.0.0)
project(ATOMIC_GOD)

set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

add_subdirectory(game/)
add_subdirectory(objects/)

target_link_libraries(${PROJECT_NAME} Game Entity Player)
