cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(turbo-spoon)

file(GLOB_RECURSE SRC_LIST src/*)
add_executable(main ${SRC_LIST})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${SRC_LIST})

set(_LIB_GLEW_PATH "libs/glew-2.2.0")
set(_LIB_GLFW_PATH "libs/glfw")
set(_LIB_GLM_PATH "libs/glm")
set(_LIB_ASSIMP_PATH "libs/assimp")
set(_LIB_SOIL_PATH "libs/soil")

set(BUILD_SHARED_LIBS OFF)

add_subdirectory("${_LIB_GLEW_PATH}/build/cmake")
add_subdirectory("${_LIB_GLFW_PATH}")
add_subdirectory("${_LIB_GLM_PATH}")
add_subdirectory("${_LIB_ASSIMP_PATH}")
add_subdirectory("${_LIB_SOIL_PATH}")

set(_LIB_GLFW_PROJ glfw update_mappings)
set(_LIB_GLEW_PROJ glew glewinfo uninstall visualinfo glew_s)
set(_LIB_ASSIMP_PROJ assimp unit UpdateAssimpLibsDebugSymbolsAndDLLs zlibstatic)
set(_LIB_SOIL_PROJ soil)

set_target_properties(${_LIB_GLFW_PROJ} PROPERTIES FOLDER "libs/GLFW3")
set_target_properties(${_LIB_GLEW_PROJ} PROPERTIES FOLDER "libs/glew")
set_target_properties(${_LIB_ASSIMP_PROJ} PROPERTIES FOLDER "libs/assimp")
set_target_properties(${_LIB_SOIL_PROJ} PROPERTIES FOLDER "libs/soil")
set_target_properties(main ${_LIB_GLFW_PROJ} ${_LIB_GLEW_PROJ} ${_LIB_ASSIMP_PROJ} ${_LIB_SOIL_PROJ} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

include_directories("${_LIB_GLEW_PATH}/include")
include_directories("${_LIB_GLFW_PATH}/include")
include_directories("${_LIB_ASSIMP_PATH}/include")
include_directories("${_LIB_GLM_PATH}")
include_directories("${_LIB_SOIL_PATH}/inc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(main PRIVATE cxx_std_17)

target_link_libraries(main glew_s glfw glm assimp soil)