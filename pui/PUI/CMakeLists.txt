set(PUI "PUI")

include_directories(include)

add_library(${PUI} SHARED src/pui.cpp src/status_bar.cpp)
target_include_directories(${PUI} PUBLIC include)

target_link_libraries(${PUI} sfml-graphics sfml-window sfml-system sfml-audio)
