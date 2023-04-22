include_directories(include)
add_library(Physics SHARED src/Physics.cpp)
target_include_directories(Physics PUBLIC include)

install(TARGETS Physics DESTINATION lib)
install(FILES include/Physics.hpp DESTINATION include)

target_link_libraries(Physics sfml-graphics sfml-window sfml-system sfml-audio)
