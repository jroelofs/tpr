cmake_minimum_required(VERSION 2.6)

project(TPR)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Version numbers
set(TPR_VERSION_MAJOR 1)
set(TPR_VERSION_MINOR 0)

set(TPR_RUNTIME_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin)
set(TPR_LIBRARY_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Configuration File
configure_file(
  "${PROJECT_SOURCE_DIR}/lib/Config/Config.h.in"
  "${PROJECT_BINARY_DIR}/include/tpr/Config/Config.h")
include_directories("${PROJECT_BINARY_DIR}")

link_directories("${PROJECT_BINARY_DIR}/lib")

add_subdirectory(lib)
add_subdirectory(tools)

