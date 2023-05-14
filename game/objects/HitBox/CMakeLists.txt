set(HIT_BOX "hit_box")

add_library(${HIT_BOX} SHARED hit_box.cpp hit_box.hpp)

target_link_libraries(${HIT_BOX} ${SFML_LIBRARIES})

# add_subdirectory(tests/)
