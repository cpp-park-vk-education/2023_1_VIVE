set(IStatus "i_status")

add_library(${IStatus} SHARED i_status.cpp i_status.hpp)

target_link_libraries(${IStatus} ${SFML_LIBRARIES})
