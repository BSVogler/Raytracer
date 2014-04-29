
#find_package( UnitTest++ REQUIRED )

add_executable(runTests main.cpp)

target_link_libraries(runTests
                      glfw
                      UnitTest++
                      )

#add_dependencies(test glfw UnitTest++ ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS runTests DESTINATION .)
