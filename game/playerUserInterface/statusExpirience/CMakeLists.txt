set(STATUS_EXPIRIENCE "status_expirience")

add_library(${STATUS_EXPIRIENCE} SHARED status_expirience.cpp status_expirience.hpp)

target_link_libraries(${STATUS_EXPIRIENCE} ${SFML_LIBRARIES})
target_link_libraries(${STATUS_EXPIRIENCE} asset_manager)
