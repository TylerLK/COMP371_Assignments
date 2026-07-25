# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("Assignment2")

# Include the necessary directories for any external libraries
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/external"
)

# Add executable files
add_executable (Assignment2 "src/main.cpp" "src/Shader.h" "src/Shader.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Assignment2 PROPERTY CXX_STANDARD 20)
endif()

# Include appropriate directory filepaths
target_include_directories(Assignment2 PRIVATE
	"${CMAKE_SOURCE_DIR}/external/glew/include"
	"${CMAKE_SOURCE_DIR}/external/glfw/include"
	"${CMAKE_SOURCE_DIR}/external"
)

# Link GLFW, GLEW, & GLM to this project
target_link_libraries(Assignment2 PRIVATE glfw glew_s opengl32 glm)

# Link GLEW to this project
target_compile_definitions(Assignment2 PRIVATE GLEW_STATIC)