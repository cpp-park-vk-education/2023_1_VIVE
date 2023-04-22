include_directories(include)
add_library(Game SHARED src/Game.cpp)
target_include_directories(Game PUBLIC include)

install(TARGETS Game DESTINATION lib)
install(FILES include/Game.hpp DESTINATION include)

target_link_libraries(Game Player)
