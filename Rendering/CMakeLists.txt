cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw.git"
  GIT_TAG        "3.3.6"
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glad
  GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
  GIT_TAG        "v0.1.36"
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
  glm
  GIT_REPOSITORY "https://github.com/g-truc/glm.git"
  GIT_TAG        "0.9.9.8"
)
FetchContent_MakeAvailable(glm)

add_library(Rendering src/glad.c src/Shader.cpp)

target_include_directories(Rendering PUBLIC ${PROJECT_SOURCE_DIR}/Rendering/include)

target_link_libraries(Rendering PUBLIC Utils ${OPENGL_LIBRARY} glfw glm)

add_custom_target(copy-shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Rendering/Shaders/ ${PROJECT_BINARY_DIR}/OpenGLGame/Shaders
    DEPENDS Rendering)