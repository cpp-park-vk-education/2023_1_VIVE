set(ATTACK "attack")

add_library(${ATTACK} SHARED attack.cpp attack.hpp)

target_link_libraries(${ATTACK} ${SFML_LIBRARIES})
target_link_libraries(${ATTACK} i_action physical_object)
