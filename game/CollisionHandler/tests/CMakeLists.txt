add_executable(collision_handler_test src/test_collision.cpp)
target_link_libraries(
    collision_handler_test collision_handler player tile enemy particle boss
    GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
