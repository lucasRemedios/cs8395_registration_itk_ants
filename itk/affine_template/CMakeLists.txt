cmake_minimum_required(VERSION 2.8)

project (affine_avg)

find_package (ITK REQUIRED)
include (${ITK_USE_FILE})

add_executable (affine_avg affine_avg.cxx)

target_link_libraries (affine_avg ${ITK_LIBRARIES})
