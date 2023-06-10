set(STATUS_BAR "status_bar")

add_library(${STATUS_BAR} SHARED status_bar.cpp status_bar.hpp)

target_link_libraries(${STATUS_BAR} ${SFML_LIBRARIES})
target_link_libraries(${STATUS_BAR} asset_manager)
