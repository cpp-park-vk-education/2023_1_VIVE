set(ITEM "item")

add_library(${ITEM} SHARED item.cpp item.hpp)

target_link_libraries(${ITEM} ${SFML_LIBRARIES})
target_link_libraries(${ITEM} object)
