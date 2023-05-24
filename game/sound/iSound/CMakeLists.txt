set(ISOUND "i_sound")

add_library(${ISOUND} SHARED i_sound.cpp i_sound.hpp sound_type.hpp)

target_link_libraries(${ISOUND} ${SFML_LIBRARIES})
