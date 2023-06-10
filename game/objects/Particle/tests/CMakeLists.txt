add_executable(particle_tests src/particle_tests.cpp)
target_link_libraries(
    particle_tests particle GTest::gtest_main 
)


# add_test(collision_handler_test collision_handler_test)
