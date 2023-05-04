aux_source_directory(src level_SRCS)

add_library(level SHARED ${level_SRCS})
target_include_directories(level PUBLIC include)
target_link_libraries(level PUBLIC iobject Player Enemy ${SFML_LIBRARIES})
