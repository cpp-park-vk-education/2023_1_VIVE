add_executable(enemy_tests src/enemy_tests.cpp)
target_link_libraries(
    enemy_tests enemy GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
