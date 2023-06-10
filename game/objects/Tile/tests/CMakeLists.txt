add_executable(tile_tests src/tile_tests.cpp)
target_link_libraries(
    tile_tests tile GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
