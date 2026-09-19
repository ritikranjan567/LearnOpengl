// LearnOpengl.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>


// glm test
// glm::vec4 vec(1.0f, 1.0f, 0.0f, 1.0f);
// glm::mat4 trans = glm::mat4(1.0f); // identify matrix

// trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // converts to translation matrix
// vec = trans * vec;
//std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

//trans = glm::rotate(trans, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate on z-direction
//// now scale it to half
//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.0));
//vec = trans * vec; // now the vec is rotated and scaled
//std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
