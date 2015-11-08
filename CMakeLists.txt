cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

set(FENSTERCHEN fensterchen)
set(FRAMEWORK_NAME framework)

project(${FENSTERCHEN})

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

if(MSVC)
  set(BINARY_DIRECTORY build)
endif()

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
  set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

option(FENSTERCHEN_IN_SOURCE_BUILD "FENSTERCHEN_IN_SOURCE_BUILD" OFF)
if(FENSTERCHEN_IN_SOURCE_BUILD)
  add_definitions(-DFENSTERCHEN_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
  add_definitions(-DFENSTERCHEN_BINARY_DIR="../")
else()
  add_definitions(-DFENSTERCHEN_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
  add_definitions(-DFENSTERCHEN_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

set(GLFW_DIRECTORY glfw-3.0.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(GLM_DIRECTORY glm-0.9.5.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_DIRECTORY})

################################
# Add libraries to executables

set(BINARY_FILES glfw ${GLFW_LIBRARIES} ${FREEIMAGE_LIBRARY})

################################
# Add output directory

if(MSVC)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COPY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Debug/ )
  else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COPY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Release/ )
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else(MSVC)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Debug )
  else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Release )
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(MSVC)

option(FENSTERCHEN_AUTOMATED_TESTS "FENSTERCHEN_AUTOMATED_TESTS" OFF)
if(FENSTERCHEN_AUTOMATED_TESTS)
  add_definitions(-DAUTOMATED_TESTS)
endif()

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  if (NOT APPLE)
    add_definitions(-fpermissive)
  endif()
endif()

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/framework)
add_subdirectory(framework)

add_subdirectory(source)

set (FENSTERCHEN_TESTS "false" CACHE BOOL "Set to enable testing.")
if (FENSTERCHEN_TESTS)
  set(UNITTEST_PP_DIRECTORY unittest-cpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${UNITTEST_PP_DIRECTORY}/UnitTest++)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${UNITTEST_PP_DIRECTORY})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${UNITTEST_PP_DIRECTORY}/UnitTest++)
  #set(BINARY_FILES UnitTest++ glfw ${GLFW_LIBRARIES} ${FREEIMAGE_LIBRARY})

  add_subdirectory(tests)
  enable_testing()
  add_test( NAME testFensterchen COMMAND runTests )
endif (FENSTERCHEN_TESTS)

install (DIRECTORY data DESTINATION .)

# See http://www.vtk.org/Wiki/CMake:CPackPackageGenerators
set (CPACK_PACKAGE_VERSION_MAJOR "4")
set (CPACK_PACKAGE_VERSION_MINOR "4")
set (CPACK_PACKAGE_VERSION_PATCH "2")
# Use current date in YYYYMMDD format as patch number

# cpack mistakenly detects Mingw-w64 as win32
if (MINGW)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set (CPACK_SYSTEM_NAME win64)
  endif ()
endif ()


if (WIN32)
  set (CPACK_GENERATOR "ZIP")
else ()
  set (CPACK_GENERATOR "TBZ2")
endif ()

include(CPack)
