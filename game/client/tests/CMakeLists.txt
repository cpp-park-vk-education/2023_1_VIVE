project(test_client)

add_executable(${PROJECT_NAME} test_main.cpp)

target_link_libraries(${PROJECT_NAME} client ${GTest_LIBRARIES})

gtest_discover_tests(${PROJECT_NAME})

