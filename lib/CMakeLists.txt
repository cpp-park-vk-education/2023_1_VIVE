AUX_SOURCE_DIRECTORY(src server_SRCS)

add_library(Server ${server_SRCS})
target_include_directories(Server PUBLIC include)

add_subdirectory(tests)