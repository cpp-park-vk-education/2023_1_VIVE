set(PLAYER "Player")

include_directories(include)
add_library(${PLAYER} SHARED src/Player.cpp)
target_include_directories(${PLAYER} PUBLIC include)

install(TARGETS ${PLAYER} DESTINATION lib)
install(FILES include/Player.hpp DESTINATION include)

target_link_libraries(${PLAYER} ${SFML_INCLUDE_DIRS})
target_link_libraries(${PLAYER} Entity)
