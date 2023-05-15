set(CAMERA_TARGET "camera_target")

add_library(${CAMERA_TARGET} SHARED camera_target.cpp camera_target.hpp)

target_link_libraries(${CAMERA_TARGET} ${SFML_LIBRARIES})
