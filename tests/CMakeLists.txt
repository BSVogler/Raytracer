
#find_package( UnitTest++ REQUIRED )

add_executable(runTests main.cpp)

target_link_libraries(runTests
                      UnitTest++
                      ${FRAMEWORK_NAME}
                      ${BINARY_FILES}
                      )

add_dependencies(example UnitTest++ glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS runTests DESTINATION .)
