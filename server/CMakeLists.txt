project(server)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} server_lib)
