set(TRIGGER "trigger")

add_library(${TRIGGER} trigger.cpp trigger.hpp)

target_link_libraries(${TRIGGER} ${SFML_LIBRARIES})
target_link_libraries(${TRIGGER} physical_object level)

# add_subdirectory(tests/)
