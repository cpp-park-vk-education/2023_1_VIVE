set (camera "camera")

add_library(${camera} SHARED camera.cpp camera.hpp)

target_link_libraries(${camera} i_camera)
