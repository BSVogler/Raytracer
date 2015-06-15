add_executable(tests main.cpp)

target_link_libraries(tests
                      ${FRAMEWORK_NAME}
                      ${LIBRARIES}
                      )

add_dependencies(tests glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

add_custom_command(
  TARGET tests POST_BUILD
  COMMAND ctest
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running tests"
  )

