set(STB_LIB_NAME "stb")
set(STB_PATH "${CMAKE_CURRENT_LIST_DIR}/${STB_LIB_NAME}")

add_library(
	"${STB_LIB_NAME}"
	STATIC
		${STB_LIB_NAME}/stb_image.h
        ${CMAKE_CURRENT_LIST_DIR}/stb_image.cpp
)
target_include_directories("${STB_LIB_NAME}" PUBLIC "${STB_PATH}")

set_target_properties("${STB_LIB_NAME}" PROPERTIES FOLDER "${LIB_DIR}")