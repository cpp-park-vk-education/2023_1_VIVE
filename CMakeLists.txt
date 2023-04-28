cmake_minimum_required(VERSION 3.0.0)
project(ATOMIC_GOD)

set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

set(Boost_DIR "boost/lib/cmake/Boost-1.82.0")
find_package(Boost)

add_executable(${PROJECT_NAME} src/main.cpp)

set(SFML_INCLUDE_DIRS sfml-graphics sfml-window sfml-system sfml-audio)

target_link_libraries(${PROJECT_NAME} ${SFML_INCLUDE_DIRS} ${Boost_LIBRARIES})

add_subdirectory(game)
add_subdirectory(objects)

target_link_libraries(${PROJECT_NAME} game button menu Entity Player)
