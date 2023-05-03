AUX_SOURCE_DIRECTORY(src client_SRCS)

add_library(client SHARED ${client_SRCS})
target_include_directories(client PUBLIC include)
