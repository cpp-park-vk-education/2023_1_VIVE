cmake_minimum_required(VERSION 3.0.0)
project(ATOMIC_GOD)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)
set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system sfml-audio)

set(SOURCE_FILE ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(GAME_DIR ${CMAKE_SOURCE_DIR}/game)

set(PLAYER_USER_INTERFACE_DIR ${GAME_DIR}/playerUserInterface)

set(ASSETMANAGERHPP ${GAME_DIR}/assetManager/asset_manager.hpp)
set(ASSETMANAGERCPP ${GAME_DIR}/assetManager/asset_manager.cpp)
set(CAMERATARGETHPP ${GAME_DIR}/cameraTarget/camera_target.hpp)
set(CAMERATARGETCPP ${GAME_DIR}/cameraTarget/camera_target.cpp)
set(NAVIGATIONICONSHPP ${PLAYER_USER_INTERFACE_DIR}/navigationIcons/navigation_icons.hpp)
set(NAVIGATIONICONSCPP ${PLAYER_USER_INTERFACE_DIR}/navigationIcons/navigation_icons.cpp)
set(STATUSMONEYHPP ${PLAYER_USER_INTERFACE_DIR}/statusMoney/status_money.hpp)
set(STATUSMONEYCPP ${PLAYER_USER_INTERFACE_DIR}/statusMoney/status_money.cpp)
set(STATUSEXPHPP ${PLAYER_USER_INTERFACE_DIR}/statusExpirience/status_expirience.hpp)
set(STATUSEXPCPP ${PLAYER_USER_INTERFACE_DIR}/statusExpirience/status_expirience.cpp)
set(STATUSBARHPP ${PLAYER_USER_INTERFACE_DIR}/statusBar/status_bar.hpp)
set(STATUSBARCPP ${PLAYER_USER_INTERFACE_DIR}/statusBar/status_bar.cpp)
set(STATUSWEAPONHPP ${PLAYER_USER_INTERFACE_DIR}/statusWeapon/status_weapon.hpp)
set(STATUSWEAPONCPP ${PLAYER_USER_INTERFACE_DIR}/statusWeapon/status_weapon.cpp)
set(PLAYERUSERINTERFACEHPP ${PLAYER_USER_INTERFACE_DIR}/playerUserInterface/player_user_interface.hpp)
set(PLAYERUSERINTERFACECPP ${PLAYER_USER_INTERFACE_DIR}/playerUserInterface/player_user_interface.cpp)

include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILE}
            ${ASSETMANAGERHPP} ${ASSETMANAGERCPP}
            ${NAVIGATIONICONSHPP} ${NAVIGATIONICONSCPP}
            ${STATUSMONEYHPP} ${STATUSMONEYCPP}
            ${STATUSEXPHPP} ${STATUSEXPCPP}
            ${STATUSBARHPP} ${STATUSBARCPP}
            ${CAMERATARGETHPP} ${CAMERATARGETCPP}
            ${STATUSWEAPONHPP} ${STATUSWEAPONCPP}
            ${PLAYERUSERINTERFACEHPP} ${PLAYERUSERINTERFACECPP})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
