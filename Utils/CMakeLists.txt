cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(Utils   "include/Utils.hpp" "src/Utils.cpp")
target_include_directories(Utils PUBLIC ${PROJECT_SOURCE_DIR}/Utils/include)