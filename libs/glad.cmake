set(GLAD_LIB_NAME "glad")
set(GLAD_SRC_PATH "${CMAKE_CURRENT_LIST_DIR}/${GLAD_LIB_NAME}/src")
set(GLAD_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/${GLAD_LIB_NAME}/include")

add_library("${GLAD_LIB_NAME}" STATIC "${GLAD_SRC_PATH}/glad.c")
target_include_directories("${GLAD_LIB_NAME}" PUBLIC "${GLAD_INCLUDE_PATH}")

set_target_properties("${GLAD_LIB_NAME}" PROPERTIES FOLDER "${LIB_DIR}")