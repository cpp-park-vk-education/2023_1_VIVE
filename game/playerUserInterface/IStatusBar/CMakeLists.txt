set(IStatusBar "i_status_bar")

add_library(${IStatusBar} SHARED i_status_bar.cpp i_status_bar.hpp)

target_link_libraries(${IStatusBar} ${SFML_LIBRARIES})
