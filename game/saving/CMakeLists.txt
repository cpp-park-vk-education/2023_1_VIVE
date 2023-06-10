aux_source_directory(src saving_SRCS)

add_library(saving SHARED ${saving_SRCS})
target_include_directories(saving PUBLIC include)
#target_link_libraries(saving PUBLIC iobject Player ${SFML_LIBRARIES})
