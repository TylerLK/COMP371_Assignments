# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("Assignment3")

# Include the necessary directories for any external libraries
include_directories(
	"${CMAKE_SOURCE_DIR}/external/glew/include"
	"${CMAKE_SOURCE_DIR}/external/glfw/include"
	"${CMAKE_SOURCE_DIR}/external"
	"${CMAKE_SOURCE_DIR}/external/tinyobjloader"
)

# Add executable files
add_executable (Assignment3
	"src/main.cpp"
	"src/Utils.h"
	"src/Utils.cpp"
	"src/driver.cpp"
	"src/Driver.H"
	"src/tiny_obj_loader.cc"
)

# Copy the shaders to the build directory
add_custom_command(TARGET Assignment3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
		$<TARGET_FILE_DIR:Assignment3>/shaders
)

# Copy the textures to the build directory
add_custom_command(TARGET Assignment3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/assets"
		$<TARGET_FILE_DIR:Assignment3>/assets
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Assignment3 PROPERTY CXX_STANDARD 20)
endif()

# Include appropriate directory filepaths
target_include_directories(Assignment3 PRIVATE
	"${CMAKE_SOURCE_DIR}/external/glew/include"
	"${CMAKE_SOURCE_DIR}/external/glfw/include"
	"${CMAKE_SOURCE_DIR}/external"
	"${CMAKE_SOURCE_DIR}/external/SOIL2/src/SOIL2"
	"${CMAKE_SOURCE_DIR}/external/tinyobjloader"
)

# Define the SOIL2 Library as an import target
add_library(SOIL2_Library STATIC IMPORTED)

set_target_properties(SOIL2_Library PROPERTIES
	IMPORTED_LOCATION_DEBUG "${CMAKE_SOURCE_DIR}/external/SOIL2/lib/windows/soil2-debug.lib"
	IMPORTED_LOCATION_RELEASE "${CMAKE_SOURCE_DIR}/external/SOIL2/lib/windows/soil2.lib"
)

# Link GLFW, GLEW, & GLM to this project
target_link_libraries(Assignment3 PRIVATE
	glfw
	glew_s
	opengl32
	glm
	SOIL2_Library
)

# Link GLEW to this project
target_compile_definitions(Assignment3 PRIVATE GLEW_STATIC)