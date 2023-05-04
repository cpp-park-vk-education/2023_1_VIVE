set (Sound "sound")

add_library(${Sound} SHARED sound.cpp sound.hpp)

target_link_libraries(${Sound} ${SFML_LIBRARIES} i_sound)
