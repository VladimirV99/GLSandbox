# Project definition
cmake_minimum_required(VERSION 3.10)
project(GLSandbox
	VERSION 1.0
)

# Source files
set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(SOURCES 
	"${SRC_PATH}/main.cpp"
    "${SRC_PATH}/common.hpp"
    "${SRC_PATH}/common.cpp"
    "${SRC_PATH}/shader.hpp"
    "${SRC_PATH}/shader.cpp"
    "${SRC_PATH}/camera.hpp"
    "${SRC_PATH}/camera.cpp"
    "${SRC_PATH}/demos/demo.hpp"
    "${SRC_PATH}/demos/triangleDemo.hpp"
    "${SRC_PATH}/demos/triangleDemo.cpp"
    "${SRC_PATH}/demos/boxesDemo.hpp"
    "${SRC_PATH}/demos/boxesDemo.cpp"
    "${SRC_PATH}/demos/normalMapDemo.hpp"
    "${SRC_PATH}/demos/normalMapDemo.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_PATH}")
set(EXECUTABLE_OUTPUT_PATH "${BUILD_PATH}")
set(VS_STARTUP_PROJECT ${PROJECT_NAME})

# Dependencies
add_subdirectory("${LIB_PATH}")
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw imgui glm stb assimp)