set(ICamera "i_camera")

add_library(${ICamera} SHARED i_camera.cpp i_camera.hpp)

target_link_libraries(${ICamera} ${SFML_LIBRARIES})
