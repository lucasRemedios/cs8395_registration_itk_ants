cmake_minimum_required(VERSION 2.8)

project (homework1)

find_package (ITK REQUIRED)
include (${ITK_USE_FILE})

add_executable (hw1 hw1.cxx)

target_link_libraries (hw1 ${ITK_LIBRARIES})
