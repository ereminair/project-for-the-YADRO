cmake_minimum_required(VERSION 3.10)
project(external_sort)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")
add_executable(external_sort ${SRC_FILES})

enable_testing()
add_subdirectory(tests)
