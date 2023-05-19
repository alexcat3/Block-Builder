cmake_minimum_required(VERSION 3.21)
project(BlockBuilder)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories( "lib/glfw/include" "lib/glad/include" "lib/stb/" "lib/")
link_directories(lib/glfw/lib)

add_executable(BlockBuilder src/main.cpp src/Shader.cpp lib/glad/src/glad.c lib/stb/stb_image.cpp src/VertexArray.cpp src/VertexArray.h src/Texture.cpp src/Texture.h src/ScreenObject.cpp src/ScreenObject.h src/CubeIdenticalFace.cpp src/CubeIdenticalFace.h src/ThreeDVec.cpp src/ThreeDVec.h src/Block.cpp src/Block.h src/World.cpp src/World.h src/Camera.cpp src/Camera.h src/Cube4Face.cpp src/Cube4Face.h src/BlockSelector.cpp src/BlockSelector.h src/Rect2D.cpp src/Rect2D.h)
target_link_libraries(BlockBuilder glfw3)

add_executable(test src/test.cpp src/Shader.cpp src/Camera.cpp src/ScreenObject.cpp src/VertexArray.cpp lib/stb/stb_image.cpp src/Texture.cpp src/Block.cpp src/CubeIdenticalFace.cpp src/World.cpp lib/glad/src/glad.c)
target_link_libraries(test glfw3)