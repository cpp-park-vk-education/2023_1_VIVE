set(playerUserInterface "player_user_interface")

add_library(${playerUserInterface} SHARED player_user_interface.cpp player_user_interface.hpp)

target_link_libraries(${playerUserInterface} navigation_icons i_status i_status_bar)
