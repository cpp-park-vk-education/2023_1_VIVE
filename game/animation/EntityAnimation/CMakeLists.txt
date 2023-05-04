set (EntityAnimation "entity_animation")

add_library(${EntityAnimation} SHARED entity_animation.cpp entity_animation.hpp)

target_link_libraries(${EntityAnimation} i_animatable)
