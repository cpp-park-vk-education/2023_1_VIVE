AUX_SOURCE_DIRECTORY(src server_SRCS)

add_library(server_lib ${server_SRCS})
target_include_directories(server_lib PUBLIC include)
