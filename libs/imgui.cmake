set(IMGUI_LIB_NAME "imgui")
set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/${IMGUI_LIB_NAME}")

add_library(
	"${IMGUI_LIB_NAME}"
	STATIC
		${IMGUI_PATH}/imgui.h
		${IMGUI_PATH}/imgui.cpp
		${IMGUI_PATH}/imgui_demo.cpp
		${IMGUI_PATH}/imgui_draw.cpp
		${IMGUI_PATH}/imgui_widgets.cpp
		${IMGUI_PATH}/examples/imgui_impl_glfw.h
		${IMGUI_PATH}/examples/imgui_impl_glfw.cpp
		${IMGUI_PATH}/examples/imgui_impl_opengl3.h
		${IMGUI_PATH}/examples/imgui_impl_opengl3.cpp
)
target_compile_definitions("${IMGUI_LIB_NAME}" PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
target_include_directories("${IMGUI_LIB_NAME}" 
	PUBLIC
		${GLFW_INCLUDE_PATH}
		${GLAD_INCLUDE_PATH}
		${IMGUI_PATH}
)

set_target_properties("${IMGUI_LIB_NAME}" PROPERTIES FOLDER "${LIB_DIR}")