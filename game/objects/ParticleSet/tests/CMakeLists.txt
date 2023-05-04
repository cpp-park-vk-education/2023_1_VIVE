add_executable(particle_set_tests src/particle_set_tests.cpp)
target_link_libraries(
    particle_set_tests particle_set GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
