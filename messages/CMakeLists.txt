AUX_SOURCE_DIRECTORY(src messages_SRCS)

add_library(messages SHARED ${messages_SRCS})
target_include_directories(messages PUBLIC include)

