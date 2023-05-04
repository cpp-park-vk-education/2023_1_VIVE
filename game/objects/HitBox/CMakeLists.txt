set(HIT_BOX "hit_box")

add_library(${HIT_BOX} SHARED hit_box.cpp hit_box.hpp)

target_link_libraries(${HIT_BOX} sfml-system sfml-window sfml-graphics sfml-audio)

add_subdirectory(tests/)
