cmake_minimum_required(VERSION 3.20)

project(AtmosphericScattering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_executable(AtmosphericScattering
	src/main.cpp
	external/glad/src/gl.c


 )

target_include_directories(AtmosphericScattering PRIVATE
	
	external/glad/include
	external/glfw/inlcude
	external/glm
)

target_link_libraries(AtmosphericScattering PRIVATE glfw)