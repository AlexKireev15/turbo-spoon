cmake_minimum_required(VERSION 3.17)
project(turbo-spoon)

add_subdirectory("E:/repos/turbo-spoon/libs/_libs_src/glew-2.2.0/build/cmake")

add_executable(main src/main.cpp)
#target_link_libraries(main GLEW::GLEW OpenGL glfw glm assimp)