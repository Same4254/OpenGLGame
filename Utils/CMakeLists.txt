cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

add_library(Utils src/Vector.cpp)
target_include_directories(Utils PUBLIC ${PROJECT_SOURCE_DIR}/Utils/include)