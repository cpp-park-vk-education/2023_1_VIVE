set(ANIMATION "animation")

add_library(${ANIMATION} SHARED animation.cpp animation.hpp)

target_link_libraries(${ANIMATION} i_animation asset_manager)