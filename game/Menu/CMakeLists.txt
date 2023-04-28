add_library(menu SHARED Menu.cpp Menu.hpp)
target_link_libraries(menu button ${SFML_INCLUDE_DIRS})
