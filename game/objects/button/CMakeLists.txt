aux_source_directory(src button_SRCS)

add_library(button STATIC ${button_SRCS})
target_include_directories(button PUBLIC include)
target_link_libraries(button PUBLIC object game)
