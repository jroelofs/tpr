cmake_minimum_required(VERSION 2.6)

project(TPR)

# Version numbers
set(TPR_VERSION_MAJOR 1)
set(TPR_VERSION_MINOR 0)

# Configuration File
configure_file(
  "${PROJECT_SOURCE_DIR}/lib/Config/Config.h.in"
  "${PROJECT_BINARY_DIR}/include/tpr/Config/Config.h")
include_directories(
  "${PROJECT_BINARY_DIR}"
  )

include_directories(
  "${PROJECT_SOURCE_DIR}/include/tpr"
  )
add_subdirectory(lib/IHex)

add_executable(tpr tools/tpr/main.cpp)
target_link_libraries(tpr IHex)
