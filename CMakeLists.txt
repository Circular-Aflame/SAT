#time: 2022.5.26
#project: OOP-SAT

cmake_minimum_required(VERSION 2.6)

project(SAT)

include_directories(include/)
add_subdirectory(source)
aux_source_directory(. DIR_SRCS)
add_executable(main ${DIR_SRCS})
target_link_libraries(main work)
