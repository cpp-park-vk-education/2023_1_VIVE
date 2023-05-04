set (AssetManager "asset_manager")

add_library(${AssetManager} SHARED asset_manager.cpp asset_manager.hpp)

target_link_libraries(${AssetManager} i_asset_manager)
