add_executable(player_tests src/player_tests.cpp)
target_link_libraries(
    player_tests player GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
