set(STATUS_WEAPON "status_weapon")

add_library(${STATUS_WEAPON} SHARED status_weapon.cpp status_weapon.hpp)

target_link_libraries(${STATUS_WEAPON} ${SFML_LIBRARIES})
target_link_libraries(${STATUS_WEAPON} asset_manager)
