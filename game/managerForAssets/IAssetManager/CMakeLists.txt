set (IAssetManager "i_asset_manager")

add_library(${IAssetManager} SHARED i_asset_manager.cpp i_asset_manager.hpp)

target_link_libraries(${IAssetManager} ${SFML_LIBRARIES})
