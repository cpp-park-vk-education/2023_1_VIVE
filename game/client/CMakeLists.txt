aux_source_directory(src client_SRCS)

add_library(client ${client_SRCS})
target_include_directories(client PUBLIC include)
target_link_libraries(client PUBLIC game messages ${BOOST_LIBRARIES})

if(BUILD_TESTS)
    add_subdirectory(tests)
endif ()