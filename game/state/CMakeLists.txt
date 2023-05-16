aux_source_directory(src state_SRCS)

add_library(state ${state_SRCS})
target_include_directories(state PUBLIC include)
target_link_libraries(state PUBLIC messages player object level button asset_manager player_user_interface)
