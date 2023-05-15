set(PLAYER_USER_INTERFACE "player_user_interface")

add_library(${PLAYER_USER_INTERFACE} SHARED player_user_interface.cpp player_user_interface.hpp)

target_link_libraries(${PLAYER_USER_INTERFACE} ${SFML_LIBRARIES})
target_link_libraries(${PLAYER_USER_INTERFACE} status_expirience navigation_icons status_weapon status_money status_bar object)
