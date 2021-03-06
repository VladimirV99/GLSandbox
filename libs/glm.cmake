set(GLM_LIB_NAME "glm")
set(GLM_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/${IMGUI_LIB_NAME}/glm")

set(GLM_TEST_ENABLE      OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS    OFF CACHE INTERNAL "" FORCE)
set(BUILD_STATIC_LIBS    OFF CACHE INTERNAL "" FORCE)
add_subdirectory("${GLM_LIB_NAME}")
