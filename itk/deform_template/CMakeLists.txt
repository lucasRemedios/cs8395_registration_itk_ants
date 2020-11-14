cmake_minimum_required(VERSION 2.8)

project (deform_avg)

find_package (ITK REQUIRED)
include (${ITK_USE_FILE})

add_executable (deform_avg deform_avg.cxx)

target_link_libraries (deform_avg ${ITK_LIBRARIES})
