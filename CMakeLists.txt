cmake_minimum_required(VERSION 3.20)

project(AtmosphericScattering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_executable(AtmosphericScattering
	src/main.cpp
	external/glad/src/gl.c
    src/core/Shader.cpp
	"src/core/Window.cpp" 
	"src/scene/Camera.cpp" 
	"src/scene/Transform.cpp" 
	"src/graphic/Mesh.cpp" 
	"src/graphic/Renderer.cpp" 
	"src/core/Input.cpp"
	external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_impl_glfw.cpp
    external/imgui/imgui_impl_opengl3.cpp
	)

target_compile_definitions(AtmosphericScattering PRIVATE
    SHADER_DIR="${CMAKE_SOURCE_DIR}/src/shaders/"
)


target_include_directories(AtmosphericScattering PRIVATE
	
	external/glad/include
	external/glfw/include
	external/imgui
	external/
)

target_link_libraries(AtmosphericScattering PRIVATE glfw)