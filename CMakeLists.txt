cmake_minimum_required(VERSION 3.0.0)
project(AtomicGod_Server VERSION 0.1.0)

add_executable(AtomicGod_Server src/main.cpp)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(Boost_DIR "../boost_1_82_0/lib/cmake/Boost-1.82.0")
find_package(Boost COMPONENTS system filesystem serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Protobuf REQUIRED)

target_link_libraries(AtomicGod_Server ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})

add_subdirectory(lib)
target_link_libraries(AtomicGod_Server Server)