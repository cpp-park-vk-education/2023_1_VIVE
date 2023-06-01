cmake_minimum_required(VERSION 3.0.0)
project(ATOMIC_GOD)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")

# # Подключаем SFML
set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system sfml-audio)

# # Подключаем Boost
set(Boost_DIR "boost/lib/cmake/Boost-1.82.0")
find_package(Boost COMPONENTS system filesystem serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# # Подключаем Protobuf
find_package(Protobuf REQUIRED)

option(BUILD_TESTS "Build tests" OFF)

# Подключаем GTest
find_package(GTest CONFIG REQUIRED)
set(GTest_LIBRARIES GTest::gtest_main)

if (BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

# Линкуем внешние библиотеки
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${Protobuf_LIBRARIES} ${SFML_LIBRARIES})

add_subdirectory(messages)
target_include_directories(messages PUBLIC messages)
#add_subdirectory(server)
add_subdirectory(game)
target_link_libraries(${PROJECT_NAME} game messages)
