﻿cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

project ("OpenGLGame")

# Include sub-projects.
add_subdirectory ("Utils")
add_subdirectory ("Rendering")
add_subdirectory ("OpenGLGame")