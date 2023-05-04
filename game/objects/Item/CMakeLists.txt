set(ITEM "item")

add_library(${ITEM} SHARED item.cpp item.hpp)

target_link_libraries(${ITEM} i_object ${SFML_LIBRARIES})
