set(SPDLOG_LIB_NAME "spdlog")
set(SPDLOG_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/${SPDLOG_LIB_NAME}/include")

add_subdirectory("${SPDLOG_LIB_NAME}")

set_target_properties("${SPDLOG_LIB_NAME}" PROPERTIES FOLDER "${LIB_DIR}")