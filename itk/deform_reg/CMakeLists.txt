cmake_minimum_required(VERSION 2.8)

project (deform)

find_package (ITK REQUIRED)
include (${ITK_USE_FILE})

add_executable (deform deform.cxx)

target_link_libraries (deform ${ITK_LIBRARIES})
