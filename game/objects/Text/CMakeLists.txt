set(TEXT "text_object")

add_library(${TEXT} text.cpp text.hpp)
target_link_libraries(${TEXT} ${SFML_LIBRARIES})
target_link_libraries(${TEXT} object asset_manager)
