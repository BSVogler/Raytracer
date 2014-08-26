add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${BINARY_FILES})
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)
