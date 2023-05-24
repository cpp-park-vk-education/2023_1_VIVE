set(SOUND "sound")

add_library(${SOUND} SHARED sound.cpp sound.hpp)

target_link_libraries(${SOUND} ${SFML_LIBRARIES} i_sound)
