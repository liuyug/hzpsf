
cmake_minimum_required(VERSION 3.5)

project(hzpsf CXX)

aux_source_directory(src SRCS)
add_definitions(-Wall -g)

add_definitions(-D__${CMAKE_SYSTEM_NAME}__)

add_executable(hzpsf ${SRCS})

# apt install libboost-program-options-dev
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(hzpsf ${Boost_LIBRARIES})
