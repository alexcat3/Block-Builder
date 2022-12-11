cmake_minimum_required(VERSION 3.21)
project(glfw_test)

set(CMAKE_CXX_STANDARD 17)

include_directories( "glfw/include" "glad/include" "stb/")
link_directories(glfw/lib)

add_executable(glfw_test main.cpp Shader.cpp glad/src/glad.c stb/stb_image.cpp VertexArray.cpp VertexArray.h Texture.cpp Texture.h ScreenObject.cpp ScreenObject.h CubeIdenticalFace.cpp CubeIdenticalFace.h ThreeDVec.cpp ThreeDVec.h Block.cpp Block.h World.cpp World.h Camera.cpp Camera.h Cube4Face.cpp Cube4Face.h BlockSelector.cpp BlockSelector.h Rect2D.cpp Rect2D.h)
target_link_libraries(glfw_test glfw3)