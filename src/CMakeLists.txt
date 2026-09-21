# CMakeList.txt : CMake project for LearnOpengl, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LearnOpengl "LearnOpengl.cpp" "LearnOpengl.h" "Shader.cpp" "Texture.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/linking/lib/glad.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/linking/lib/stb.cpp")

set(GLFW_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/linking/lib/GLFW")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(GLFW_LIBRARY "${GLFW_ROOT}/lib-mingw-w64/libglfw3.a")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if (MSVC_VERSION GREATER_EQUAL 1950)
		set(GLFW_LIBRARY "${GLFW_ROOT}/lib-vc2026/glfw3.lib")
	else()
		set(GLFW_LIBRARY "${GLFW_ROOT}/lib-vc2022/glfw3.lib")
	endif()
else()
	message(FATAL_ERROR "Unsupported C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if (NOT EXISTS "${GLFW_LIBRARY}")
	message(FATAL_ERROR "GLFW library was not found: ${GLFW_LIBRARY}")
endif()

target_include_directories(LearnOpengl PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/linking/include)
target_link_libraries(LearnOpengl PRIVATE
	${GLFW_LIBRARY}
	opengl32)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LearnOpengl PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
