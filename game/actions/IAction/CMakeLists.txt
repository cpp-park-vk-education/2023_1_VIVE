set(I_ACTION "i_action")

add_library(${I_ACTION} SHARED i_action.cpp i_action.hpp)

target_link_libraries(${I_ACTION} ${SFML_LIBRARIES})
target_link_libraries(${I_ACTION} entity)
