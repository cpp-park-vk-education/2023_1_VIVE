add_executable(boss_tests src/boss_tests.cpp)
target_link_libraries(
    boss_tests boss GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
