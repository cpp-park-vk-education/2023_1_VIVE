set(IANIMATION "i_animation")

add_library(${IANIMATION} SHARED i_animation.cpp i_animation.hpp)

target_link_libraries(${IANIMATION} ${SFML_LIBRARIES})
