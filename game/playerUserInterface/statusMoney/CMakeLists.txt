set(STATUS_MONEY "status_money")

add_library(${STATUS_MONEY} SHARED status_money.cpp status_money.hpp)

target_link_libraries(${STATUS_MONEY} ${SFML_LIBRARIES})
target_link_libraries(${STATUS_MONEY} asset_manager)
