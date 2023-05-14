set(INVENTORY "inventory")

add_library(${INVENTORY} SHARED inventory.cpp inventory.hpp)

target_link_libraries(${INVENTORY} ${SFML_LIBRARIES})
target_link_libraries(${INVENTORY} item)
