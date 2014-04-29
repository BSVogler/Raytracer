
add_executable(example example.cpp)
#add_test(buffer-uniform COMMAND $<TARGET_FILE:example>)

target_link_libraries(example ${FRAMEWORK_NAME} ${BINARY_FILES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)
