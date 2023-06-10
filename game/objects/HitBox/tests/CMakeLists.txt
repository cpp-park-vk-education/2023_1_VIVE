add_executable(hot_box_tests src/hit_box_tests.cpp)
target_link_libraries(
    hot_box_tests hit_box GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
