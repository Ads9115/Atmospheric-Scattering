cmake_minimum_required(VERSION 3.20)

project(AtmosphericScattering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_executable(AtmosphericScattering
	src/main.cpp
	external/glad/src/gl.c
    src/core/Shader.cpp
 "src/core/Window.h" "src/core/Window.cpp" "src/scene/Camera.cpp" "src/scene/Camera.h" "src/scene/Transform.h" "src/scene/Transform.cpp" "src/graphic/Mesh.h" "src/graphic/Mesh.cpp" "src/graphic/Renderer.h" "src/graphic/Renderer.cpp" "src/core/Input.h" "src/core/Input.cpp")

target_compile_definitions(AtmosphericScattering PRIVATE
    SHADER_DIR="${CMAKE_SOURCE_DIR}/src/shaders/"
)


target_include_directories(AtmosphericScattering PRIVATE
	
	external/glad/include
	external/glfw/include
	external/
)

target_link_libraries(AtmosphericScattering PRIVATE glfw)