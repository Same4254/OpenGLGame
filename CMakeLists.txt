cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

project ("OpenGLGame")

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

FetchContent_Declare(
  assimp
  GIT_REPOSITORY "https://github.com/assimp/assimp.git"
  GIT_TAG        "v5.2.5"
  UPDATE_COMMAND  ""
)
FetchContent_MakeAvailable(assimp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(OpenGLGame "src/OpenGLGame.c" "src/glad.c" "src/Utils/Utils.c" "src/Utils/Matrix.c" "src/Rendering/Shader.c" "src/Utils/FileIO.c" "src/Rendering/Camera.c" "src/Rendering/Mesh.c")

target_link_libraries (OpenGLGame ${OPENGL_LIBRARY} glfw glm assimp)

add_custom_target(copy-shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Shaders/ ${PROJECT_BINARY_DIR}/Shaders
        DEPENDS OpenGLGame)

add_custom_target(copy-test-assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/TestAssets ${PROJECT_BINARY_DIR}/TestAssets
        DEPENDS OpenGLGame)
