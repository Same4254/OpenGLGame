cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/OpenGLGame/include)

add_executable(OpenGLGame src/OpenGLGame.cpp )

target_link_libraries (OpenGLGame Utils Rendering)

#include_directories(${PROJECT_SOURCE_DIR}/OpenGLGame/include)

#add_executable (OpenGLGame  "src/OpenGLGame.cpp")

#add_custom_target(copy-shaders ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/ ${CMAKE_CURRENT_BINARY_DIR}/Shaders
#    DEPENDS OpenGLGame)

#target_link_libraries(OpenGLGame ${OPENGL_LIBRARY} glfw glm)