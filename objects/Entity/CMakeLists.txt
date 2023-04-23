set(ENTITY "Entity")

include_directories(include)
add_library(${ENTITY} SHARED src/Entity.cpp)
target_include_directories(${ENTITY} PUBLIC include)

target_link_libraries(${ENTITY} sfml-graphics sfml-window sfml-system sfml-audio)
