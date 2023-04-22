include_directories(include)
add_library(Player SHARED src/Player.cpp)
target_include_directories(Player PUBLIC include)

install(TARGETS Player DESTINATION lib)
install(FILES include/Player.hpp DESTINATION include)

target_link_libraries(Player Physics)
