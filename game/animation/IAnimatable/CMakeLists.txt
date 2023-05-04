set(IAnimatable "i_animatable")

add_library(${IAnimatable} SHARED i_animatable.cpp i_animatable.hpp)

target_link_libraries(${IAnimatable} ${SFML_LIBRARIES})
