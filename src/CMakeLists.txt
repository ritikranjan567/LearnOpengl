# CMakeList.txt : CMake project for LearnOpengl, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LearnOpengl "LearnOpengl.cpp" "LearnOpengl.h" "glad.c")

target_link_libraries(LearnOpengl PUBLIC opengl32.lib)
target_include_directories(LearnOpengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/linking/include)
target_link_directories(LearnOpengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/linking/lib)
target_link_libraries(LearnOpengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/linking/lib/GLFW/glfw3.lib)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LearnOpengl PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
